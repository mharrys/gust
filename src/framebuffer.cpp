#include "framebuffer.hpp"

#include "framebufferimpl.hpp"
#include "renderstate.hpp"

gst::Framebuffer::Framebuffer(
    Texture & color,
    Renderbuffer & depth)
    : impl(std::make_shared<FramebufferImpl>()),
      color(color),
      depth(depth),
      color_dirty(true),
      depth_dirty(true)
{
}

bool gst::Framebuffer::operator==(Framebuffer const & other)
{
    return impl == other.impl;
}

bool gst::Framebuffer::operator!=(Framebuffer const & other)
{
    return !(*this == other);
}

gst::Framebuffer::operator bool() const
{
    return impl != nullptr;
}

void gst::Framebuffer::attach(Texture & color)
{
    this->color = color;
    color_dirty = true;
}

void gst::Framebuffer::attach(Renderbuffer & depth)
{
    this->depth = depth;
    depth_dirty = true;
}

gst::Texture gst::Framebuffer::get_color() const
{
    return color;
}

gst::Renderbuffer gst::Framebuffer::get_depth() const
{
    return depth;
}

std::vector<std::string> gst::Framebuffer::get_status() const
{
    return status;
}

void gst::Framebuffer::refresh(RenderState & render_state)
{
    if (color_dirty) {
        color_dirty = false;
        render_state.set_texture(color);
        impl->attach(*color.impl.get());
    }

    if (depth_dirty) {
        depth_dirty = false;
        render_state.set_renderbuffer(depth);
        impl->attach(*depth.impl.get());
    }

    status = impl->check_status();
}
