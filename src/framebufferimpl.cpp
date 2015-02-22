#include "framebufferimpl.hpp"

#include "renderbuffer.hpp"
#include "renderstate.hpp"
#include "texture.hpp"

gst::FramebufferImpl::FramebufferImpl(std::shared_ptr<GraphicsDevice> device)
    : handle(device->create_framebuffer()),
      device(device),
      color_dirty(false),
      depth_dirty(false)
{
}

gst::FramebufferImpl::~FramebufferImpl()
{
    device->destroy_framebuffer(handle);
}

void gst::FramebufferImpl::attach(std::shared_ptr<Texture> color)
{
    this->color = color;
    color_dirty = true;
}

void gst::FramebufferImpl::attach(std::shared_ptr<Renderbuffer> depth)
{
    this->depth = depth;
    depth_dirty = true;
}

std::shared_ptr<gst::Texture> gst::FramebufferImpl::get_color() const
{
    return color;
}

std::shared_ptr<gst::Renderbuffer> gst::FramebufferImpl::get_depth() const
{
    return depth;
}

std::vector<std::string> gst::FramebufferImpl::get_status() const
{
    return status;
}

void gst::FramebufferImpl::bind()
{
    device->bind_framebuffer(handle);
}

void gst::FramebufferImpl::sync(RenderState & render_state)
{
    if (color_dirty) {
        color_dirty = false;
        render_state.set_texture(color);
        device->framebuffer_texture_2d(color->get_handle());
    }

    if (depth_dirty) {
        depth_dirty = false;
        render_state.set_renderbuffer(depth);
        device->framebuffer_renderbuffer(depth->get_handle());
    }

    status = device->check_framebuffer_status();
}
