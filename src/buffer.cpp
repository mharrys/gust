#include "buffer.hpp"

#include "bufferimpl.hpp"
#include "renderstate.hpp"

gst::Buffer::Buffer(
    std::shared_ptr<RenderState> render_state,
    BufferTarget target)
    : impl(std::make_shared<BufferImpl>(target)),
      render_state(render_state)
{
}

bool gst::Buffer::operator==(Buffer const & other)
{
    return impl == other.impl;
}

bool gst::Buffer::operator!=(Buffer const & other)
{
    return !(*this == other);
}

gst::Buffer::operator bool() const
{
    return impl != nullptr;
}

void gst::Buffer::buffer_data(int64_t size, void const * data, DataUsage usage)
{
    push();
    impl->buffer_data(size, data, usage);
    pop();
}

void gst::Buffer::buffer_sub_data(int64_t offset, int64_t size, void const * data)
{
    push();
    impl->buffer_sub_data(offset, size, data);
    pop();
}

void gst::Buffer::define(VertexAttrib const & attrib)
{
    impl->define(attrib);
}

void gst::Buffer::push()
{
    render_state->push();
    render_state->set_buffer(*this);
}

void gst::Buffer::pop()
{
    render_state->pop();
}
