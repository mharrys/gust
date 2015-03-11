#include "framebufferimpl.hpp"

gst::FramebufferImpl::FramebufferImpl(FramebufferAttachment color, FramebufferAttachment depth)
    : color(color),
      depth(depth)
{
    needs_update();
}

void gst::FramebufferImpl::set_color(FramebufferAttachment color)
{
    this->color = color;
    needs_update();
}

void gst::FramebufferImpl::set_depth(FramebufferAttachment depth)
{
    this->depth = depth;
    needs_update();
}

gst::FramebufferAttachment gst::FramebufferImpl::get_color() const
{
    return color;
}

gst::FramebufferAttachment gst::FramebufferImpl::get_depth() const
{
    return depth;
}
