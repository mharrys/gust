#include "framebufferimpl.hpp"

#include "renderbuffer.hpp"
#include "texture.hpp"

gst::FramebufferImpl::FramebufferImpl(
    std::shared_ptr<Texture> color,
    std::shared_ptr<Renderbuffer> depth)
    : color(color),
      depth(depth)
{
    needs_update();
}

void gst::FramebufferImpl::attach(std::shared_ptr<Texture> color)
{
    this->color = color;
    needs_update();
}

void gst::FramebufferImpl::attach(std::shared_ptr<Renderbuffer> depth)
{
    this->depth = depth;
    needs_update();
}

std::shared_ptr<gst::Texture> gst::FramebufferImpl::get_color() const
{
    return color;
}

std::shared_ptr<gst::Renderbuffer> gst::FramebufferImpl::get_depth() const
{
    return depth;
}
