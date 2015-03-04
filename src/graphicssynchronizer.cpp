#include "graphicssynchronizer.hpp"

#include "framebuffer.hpp"
#include "image.hpp"
#include "graphicsdevice.hpp"
#include "logger.hpp"
#include "renderbuffer.hpp"
#include "resolution.hpp"
#include "shadoweddata.hpp"
#include "shader.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "vertexarray.hpp"

gst::GraphicsSynchronizer::GraphicsSynchronizer(
    std::shared_ptr<GraphicsDevice> device,
    std::shared_ptr<Logger> logger)
    : device(device),
      logger(logger)
{
}

void gst::GraphicsSynchronizer::bind(Buffer & buffer)
{
    if (!buffer.name) {
        buffer.name = device->create_buffer();
        buffer.cleanup = std::bind(&GraphicsDevice::destroy_buffer, device, buffer.name);
    }
    device->bind_buffer(buffer.name, buffer.get_target());
}

void gst::GraphicsSynchronizer::bind(Framebuffer & framebuffer)
{
    if (!framebuffer.name) {
        framebuffer.name = device->create_framebuffer();
        framebuffer.cleanup = std::bind(&GraphicsDevice::destroy_framebuffer, device, framebuffer.name);
    }
    device->bind_framebuffer(framebuffer.name);
}

void gst::GraphicsSynchronizer::bind(Program & program)
{
    if (!program.name) {
        program.name = device->create_program();
        program.cleanup = std::bind(&GraphicsDevice::destroy_program, device, program.name);
    }

    // synchronize shaders first since program must have shaders attached
    // before installing it

    bool shader_dirty = false;
    for (auto shader : program.get_shaders()) {
        shader_dirty = shader->dirty ? true : shader_dirty;
        bind(*shader);
        update(*shader);
    }

    if (shader_dirty) {
        for (auto shader : program.get_shaders()) {
            device->attach_shader(program.name, shader->name);
        }

        for (auto location : program.get_attribute_locations()) {
            device->bind_attribute_location(program.name, location.first, location.second);
        }

        device->link_program(program.name);
        if (!device->get_link_status(program.name)) {
            auto error = device->get_link_error(program.name);
            logger->log(TRACE("could not link program: " + error));
        }

        // safe to detach after linking
        for (auto shader : program.get_shaders()) {
            device->detach_shader(program.name, shader->name);
        }
    }

    device->use_program(program.name);
}

void gst::GraphicsSynchronizer::bind(Renderbuffer & renderbuffer)
{
    if (!renderbuffer.name) {
        renderbuffer.name = device->create_renderbuffer();
        renderbuffer.cleanup = std::bind(&GraphicsDevice::destroy_renderbuffer, device, renderbuffer.name);
    }
    device->bind_renderbuffer(renderbuffer.name);
}

void gst::GraphicsSynchronizer::bind(Shader & shader)
{
    if (!shader.name) {
        shader.name = device->create_shader(shader.get_type());
        shader.cleanup = std::bind(&GraphicsDevice::destroy_shader, device, shader.name);
    }
}

void gst::GraphicsSynchronizer::bind(Texture & texture, int unit)
{
    if (!texture.name) {
        texture.name = device->create_texture();
        texture.cleanup = std::bind(&GraphicsDevice::destroy_texture, device, texture.name);
    }
    device->bind_texture(texture.name, texture.get_target(), unit);
}

void gst::GraphicsSynchronizer::bind(VertexArray & vertex_array)
{
    if (!vertex_array.name) {
        vertex_array.name = device->create_vertex_array();
        vertex_array.cleanup = std::bind(&GraphicsDevice::destroy_vertex_array, device, vertex_array.name);
    }
    device->bind_vertex_array(vertex_array.name);
}

void gst::GraphicsSynchronizer::update(Buffer & buffer)
{
    if (!buffer.dirty) {
        return;
    }

    device->buffer_data(buffer.get_target(), *buffer.get_shadowed_data(), buffer.get_usage());
    buffer.dirty = false;
}

void gst::GraphicsSynchronizer::update(Framebuffer & framebuffer)
{
    if (!framebuffer.dirty) {
        return;
    }

    const auto color = framebuffer.get_color();
    const auto depth = framebuffer.get_depth();
    device->framebuffer_texture_2d(color->name);
    device->framebuffer_renderbuffer(depth->name);
    framebuffer.dirty = false;
}

void gst::GraphicsSynchronizer::update(Program & program)
{
    if (!program.dirty) {
        return;
    }

    for (auto uniform : program.get_uniforms()) {
        const auto annotation = uniform.first;
        const auto location = device->get_uniform_location(program.name, annotation);
        if (location == -1) {
            logger->log(TRACE("could not get uniform location for \"" + annotation + "\""));
        }
        const auto data = uniform.second;

        switch (data->get_type()) {
        case DataType::NONE:
            logger->log(TRACE("attempted to update uniform \"" + annotation + "\" with no allocated data"));
            break;
        case DataType::BOOL:
            device->uniform_int(location, data->get_bool());
            break;
        case DataType::INT:
            device->uniform_int(location, data->get_int());
            break;
        case DataType::FLOAT:
            device->uniform_float(location, data->get_float());
            break;
        case DataType::VEC2:
            device->uniform_vec2(location, data->get_vec2());
            break;
        case DataType::VEC3:
            device->uniform_vec3(location, data->get_vec3());
            break;
        case DataType::VEC4:
            device->uniform_vec4(location, data->get_vec4());
            break;
        case DataType::MAT3:
            device->uniform_matrix3(location, 1, false, data->get_float_array());
            break;
        case DataType::MAT4:
            device->uniform_matrix4(location, 1, false, data->get_float_array());
            break;
        case DataType::INT_ARRAY:
            device->uniform_int_array(location, data->get_int_array());
            break;
        case DataType::FLOAT_ARRAY:
            device->uniform_float_array(location, data->get_float_array());
            break;
        case DataType::UNSIGNED_INT:
        case DataType::UNSIGNED_INT_ARRAY:
        case DataType::VEC2_ARRAY:
        case DataType::VEC3_ARRAY:
        case DataType::VEC4_ARRAY:
            logger->log(TRACE("unsupported data type for uniform \"" + annotation + "\""));
            break;
        }
    }
    program.dirty = false;
}

void gst::GraphicsSynchronizer::update(Renderbuffer & renderbuffer)
{
    if (!renderbuffer.dirty) {
        return;
    }

    device->renderbuffer_storage(renderbuffer.get_size(), renderbuffer.get_format());
    renderbuffer.dirty = false;
}

void gst::GraphicsSynchronizer::update(Shader & shader)
{
    if (!shader.dirty) {
        return;
    }

    device->compile_shader(shader.name, shader.get_source());
    if (!device->get_compile_status(shader.name)) {
        auto error = device->get_compile_error(shader.name);
        logger->log(TRACE("could not compile shader (" + shader.get_source() + "): " + error));
    }
    shader.dirty = false;
}

void gst::GraphicsSynchronizer::update(Texture & texture)
{
    if (!texture.dirty) {
        return;
    }

    const auto target = texture.get_target();
    const auto param = texture.get_param();
    const auto image = gst::Image(texture.get_size(), texture.get_data());
    device->texture_parameters(target, param);
    device->texture_image_2d(target, image, param);
    texture.dirty = false;
}

void gst::GraphicsSynchronizer::update(VertexArray & vertex_array)
{
    if (!vertex_array.dirty) {
        return;
    }

    for (auto vertex_buffer : vertex_array.get_vertex_buffers()) {
        bind(*vertex_buffer.first);
        update(*vertex_buffer.first);
        for (auto attribute : vertex_buffer.second) {
            device->enable_vertex_attribute(attribute);
        }
    }
    bind(*vertex_array.get_index_buffer());
    update(*vertex_array.get_index_buffer());
    vertex_array.dirty = false;
}
