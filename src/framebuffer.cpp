#include "framebuffer.hpp"

#include "framebufferimpl.hpp"
#include "renderstate.hpp"

gst::Framebuffer::Framebuffer(
        std::shared_ptr<RenderState> render_state,
        Texture & color,
        Renderbuffer & depth)
    : impl(std::make_shared<FramebufferImpl>()),
      render_state(render_state),
      color(color),
      depth(depth)
{
    push();
    impl->attach(*color.impl.get());
    impl->attach(*depth.impl.get());
    pop();
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

gst::Texture & gst::Framebuffer::get_color()
{
    return color;
}

gst::Renderbuffer & gst::Framebuffer::get_depth()
{
    return depth;
}

std::vector<std::string> gst::Framebuffer::check_status()
{
    push();
    auto errors = impl->check_status();
    pop();
    return errors;
}

void gst::Framebuffer::push()
{
    render_state->push();
    render_state->set_framebuffer(*this);
}

void gst::Framebuffer::pop()
{
    render_state->pop();
}
