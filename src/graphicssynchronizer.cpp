#include "graphicssynchronizer.hpp"

#include "buffer.hpp"
#include "framebuffer.hpp"
#include "framebufferattachment.hpp"
#include "image.hpp"
#include "indexbuffer.hpp"
#include "graphicsdevice.hpp"
#include "logger.hpp"
#include "renderbuffer.hpp"
#include "resolution.hpp"
#include "shadoweddata.hpp"
#include "shader.hpp"
#include "program.hpp"
#include "texture2d.hpp"
#include "texturecube.hpp"
#include "vertexarray.hpp"
#include "vertexbuffer.hpp"

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
        program_location_cache[program.name] = LocationCache();
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

    device->buffer_data(buffer.get_target(), buffer.get_shadowed_data(), buffer.get_usage());
    buffer.dirty = false;
}

void gst::GraphicsSynchronizer::update(Framebuffer & framebuffer)
{
    if (!framebuffer.dirty) {
        return;
    }

    attach(framebuffer.get_color(), AttachmentPoint::COLOR);
    attach(framebuffer.get_depth(), AttachmentPoint::DEPTH);
    framebuffer.dirty = false;
}

void gst::GraphicsSynchronizer::update(Program & program)
{
    if (!program.dirty) {
        return;
    }

    for (auto uniform : program.get_uniforms()) {
        const auto annotation = uniform.first;
        const auto location = get_cached_uniform_location(program.name, annotation);

        if (location == -1) {
            continue;
        }

        const auto data = uniform.second;

        if (data->get_type() == DataType::NONE) {
            logger->log(TRACE("attempted to update uniform \"" + annotation + "\" with no allocated data"));
            continue;
        }

        device->uniform(location, *data);
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

    switch (texture.get_target()) {
    case TextureTarget::TEXTURE_2D:
        update_storage(static_cast<Texture2D&>(texture));
        break;
    case TextureTarget::TEXTURE_CUBE:
        update_storage(static_cast<TextureCube&>(texture));
        break;
    }

    device->update_texture_parameters(texture);
    texture.dirty = false;
}

int gst::GraphicsSynchronizer::get_cached_uniform_location(
    ResourceName name,
    std::string const & annotation)
{
    auto & locations = program_location_cache.at(name);

    if (locations.count(annotation) == 0) {
        const int location = device->get_uniform_location(name, annotation);
        locations[annotation] = location;
        if (location == -1) {
            logger->log(TRACE("could not get uniform location for \"" + annotation + "\""));
        }
    }

    return locations.at(annotation);
}

void gst::GraphicsSynchronizer::update(VertexArray & vertex_array)
{
    if (!vertex_array.dirty) {
        return;
    }

    for (auto * vertex_buffer : vertex_array.get_vertex_buffers()) {
        bind(*vertex_buffer);
        update(*vertex_buffer);
        for (auto attribute : vertex_buffer->get_attributes()) {
            device->enable_vertex_attribute(attribute);
        }
    }

    auto & index_buffer = vertex_array.get_index_buffer();
    bind(index_buffer);
    update(index_buffer);

    vertex_array.dirty = false;
}

void gst::GraphicsSynchronizer::attach(
    FramebufferAttachment const & attachment,
    AttachmentPoint attachment_point)
{
    auto resource = attachment.get_attachment();

    if (!resource) {
        return;
    }

    auto attachment_name = resource->name;
    auto attachment_type = attachment.get_type();
    device->attach_to_framebuffer(attachment_name, attachment_type, attachment_point);
}

void gst::GraphicsSynchronizer::update_storage(Texture2D const & texture)
{
    const auto internal = texture.get_internal_format();
    const auto source = texture.get_source_format();
    const auto size = texture.get_size();

    device->update_texture_storage(internal, source, size, texture.get_data());
}

void gst::GraphicsSynchronizer::update_storage(TextureCube const & texture)
{
    const auto internal = texture.get_internal_format();
    const auto source = texture.get_source_format();
    const auto size = texture.get_size();

    for (auto face : CUBE_FACES) {
        device->update_texture_storage(internal, source, size, texture.get_data(face), face);
    }
}
