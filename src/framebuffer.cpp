#include "framebuffer.hpp"

#include "framebufferimpl.hpp"
#include "renderstate.hpp"
#include "renderbufferimpl.hpp"
#include "texture2d.hpp"

gst::Framebuffer::Framebuffer(
    std::shared_ptr<Texture> color,
    std::shared_ptr<Renderbuffer> depth)
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

void gst::Framebuffer::attach(std::shared_ptr<Texture> color)
{
    this->color = color;
    color_dirty = true;
}

void gst::Framebuffer::attach(std::shared_ptr<Renderbuffer> depth)
{
    this->depth = depth;
    depth_dirty = true;
}

std::shared_ptr<gst::Texture> gst::Framebuffer::get_color() const
{
    return color;
}

std::shared_ptr<gst::Renderbuffer> gst::Framebuffer::get_depth() const
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
        if (auto tex_2d = std::dynamic_pointer_cast<Texture2d>(color)) {
            impl->attach(*tex_2d);
        }
    }

    if (depth_dirty) {
        depth_dirty = false;
        render_state.set_renderbuffer(depth);
        if (auto rb_impl = std::dynamic_pointer_cast<RenderbufferImpl>(depth)) {
            impl->attach(*rb_impl);
        }
    }

    status = impl->check_status();
}
