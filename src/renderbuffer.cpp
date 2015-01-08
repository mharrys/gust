#include "renderbuffer.hpp"

#include "renderbufferimpl.hpp"
#include "renderstate.hpp"

gst::Renderbuffer::Renderbuffer(
    std::shared_ptr<RenderState> render_state,
    Resolution size,
    RenderbufferFormat format)
    : impl(std::make_shared<RenderbufferImpl>()),
      render_state(render_state)
{
    update(size, format);
}

bool gst::Renderbuffer::operator==(Renderbuffer const & other)
{
    return impl == other.impl;
}

bool gst::Renderbuffer::operator!=(Renderbuffer const & other)
{
    return !(*this == other);
}

gst::Renderbuffer::operator bool() const
{
    return impl != nullptr;
}

void gst::Renderbuffer::update(Resolution size)
{
    push();
    impl->storage(size);
    pop();
}

void gst::Renderbuffer::update(RenderbufferFormat format)
{
    push();
    impl->storage(format);
    pop();
}

void gst::Renderbuffer::update(Resolution size, RenderbufferFormat format)
{
    push();
    impl->storage(size, format);
    pop();
}

void gst::Renderbuffer::push()
{
    render_state->push();
    render_state->set_renderbuffer(*this);
}

void gst::Renderbuffer::pop()
{
    render_state->pop();
}
