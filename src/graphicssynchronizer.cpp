#include "graphicssynchronizer.hpp"

#include "framebuffer.hpp"
#include "image.hpp"
#include "graphicsdevice.hpp"
#include "renderbuffer.hpp"
#include "resolution.hpp"
#include "shadoweddata.hpp"
#include "texture.hpp"
#include "vertexarray.hpp"

gst::GraphicsSynchronizer::GraphicsSynchronizer(std::shared_ptr<GraphicsDevice> device)
    : device(device)
{
}

void gst::GraphicsSynchronizer::sync(Buffer & buffer)
{
    if (!buffer.name) {
        buffer.name = device->create_buffer();
        buffer.cleanup = std::bind(&GraphicsDevice::destroy_buffer, device, buffer.name);
    }

    device->bind_buffer(buffer.name, buffer.get_target());

    if (buffer.dirty) {
        buffer.dirty = false;
        device->buffer_data(buffer.get_target(), *buffer.get_shadowed_data(), buffer.get_usage());
    }
}

void gst::GraphicsSynchronizer::sync(Renderbuffer & renderbuffer)
{
    if (!renderbuffer.name) {
        renderbuffer.name = device->create_renderbuffer();
        renderbuffer.cleanup = std::bind(&GraphicsDevice::destroy_renderbuffer, device, renderbuffer.name);
    }

    device->bind_renderbuffer(renderbuffer.name);

    if (renderbuffer.dirty) {
        renderbuffer.dirty = false;
        device->renderbuffer_storage(renderbuffer.get_size(), renderbuffer.get_format());
    }
}

void gst::GraphicsSynchronizer::sync(Texture & texture, int unit)
{
    if (!texture.name) {
        texture.name = device->create_texture();
        texture.cleanup = std::bind(&GraphicsDevice::destroy_texture, device, texture.name);
    }

    device->bind_texture(texture.name, texture.get_target(), unit);

    if (texture.dirty) {
        texture.dirty = false;
        const auto target = texture.get_target();
        const auto param = texture.get_param();
        const auto image = gst::Image(texture.get_size(), texture.get_data());
        device->texture_parameters(target, param);
        device->texture_image_2d(target, image, param);
    }
}

void gst::GraphicsSynchronizer::sync(Framebuffer & framebuffer)
{
    if (!framebuffer.name) {
        framebuffer.name = device->create_framebuffer();
        framebuffer.cleanup = std::bind(&GraphicsDevice::destroy_framebuffer, device, framebuffer.name);
    }

    device->bind_framebuffer(framebuffer.name);

    if (framebuffer.dirty) {
        framebuffer.dirty = false;
        const auto color = framebuffer.get_color();
        const auto depth = framebuffer.get_depth();
        device->framebuffer_texture_2d(color->name);
        device->framebuffer_renderbuffer(depth->name);
    }
}

void gst::GraphicsSynchronizer::sync(VertexArray & vertex_array)
{
    if (!vertex_array.name) {
        vertex_array.name = device->create_vertex_array();
        vertex_array.cleanup = std::bind(&GraphicsDevice::destroy_vertex_array, device, vertex_array.name);
    }

    device->bind_vertex_array(vertex_array.name);

    if (vertex_array.dirty) {
        vertex_array.dirty = false;
        // TODO: update vertex attributes here
    }
}
