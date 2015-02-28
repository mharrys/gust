#include "graphicssynchronizer.hpp"

#include "framebuffer.hpp"
#include "image.hpp"
#include "graphicsdevice.hpp"
#include "renderbuffer.hpp"
#include "resolution.hpp"
#include "texture.hpp"

gst::GraphicsSynchronizer::GraphicsSynchronizer(std::shared_ptr<GraphicsDevice> device)
    : device(device)
{
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
