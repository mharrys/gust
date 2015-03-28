#include "framebufferimpl.hpp"

#include "renderbufferimpl.hpp"
#include "texture2d.hpp"

gst::FramebufferImpl gst::FramebufferImpl::create(Resolution size)
{
    auto color = std::make_shared<Texture2D>(size);
    color->set_wrap_s(WrapMode::CLAMP_TO_EDGE);
    color->set_wrap_t(WrapMode::CLAMP_TO_EDGE);

    auto format = RenderbufferFormat::DEPTH_COMPONENT32;
    auto depth = std::make_shared<RenderbufferImpl>(size, format);

    auto framebuffer = FramebufferImpl();
    framebuffer.set_color({ color });
    framebuffer.set_depth({ depth });

    return framebuffer;
}

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

gst::FramebufferAttachment gst::FramebufferImpl::get_color_attachment() const
{
    return color;
}

gst::FramebufferAttachment gst::FramebufferImpl::get_depth_attachment() const
{
    return depth;
}
