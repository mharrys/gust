#include "vertexarray.hpp"

#include "renderstate.hpp"
#include "vertexarrayimpl.hpp"

gst::VertexArray::VertexArray(std::shared_ptr<RenderState> render_state)
    : impl(std::make_shared<VertexArrayImpl>()),
      render_state(render_state)
{
}

bool gst::VertexArray::operator==(VertexArray const & other)
{
    return impl == other.impl;
}

bool gst::VertexArray::operator!=(VertexArray const & other)
{
    return !(*this == other);
}

gst::VertexArray::operator bool() const
{
    return impl != nullptr;
}

void gst::VertexArray::draw(DrawMode mode, int first, int count)
{
    push();
    impl->draw_arrays(mode, first, count);
    pop();
}

void gst::VertexArray::draw(DrawMode mode, int count, DataType type)
{
    push();
    impl->draw_elements(mode, count, type);
    pop();
}

void gst::VertexArray::push()
{
    render_state->push();
    render_state->set_vertex_array(*this);
}

void gst::VertexArray::pop()
{
    render_state->pop();
}
