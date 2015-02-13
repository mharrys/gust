#include "vertexarray.hpp"

#include "renderstate.hpp"
#include "vertexarrayimpl.hpp"

gst::VertexArray::VertexArray()
    : impl(std::make_shared<VertexArrayImpl>()),
      vertices_dirty(false),
      indices_dirty(false)
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
    impl->draw_arrays(mode, first, count);
}

void gst::VertexArray::draw(DrawMode mode, int count, VertexDataType type)
{
    impl->draw_elements(mode, count, type);
}

void gst::VertexArray::add(std::shared_ptr<VertexBuffer> vertices)
{
    vertex_buffers.push_back(vertices);
    vertices_dirty = true;
}

void gst::VertexArray::set(std::shared_ptr<IndexBuffer> indices)
{
    this->indices = indices;
    indices_dirty = true;
}

void gst::VertexArray::refresh(RenderState & render_state)
{
    if (vertices_dirty) {
        vertices_dirty = false;
        for (auto vertices : vertex_buffers) {
            render_state.set_buffer(*vertices.get());
            for (auto attribute : vertices->attributes) {
                impl->define(attribute);
            }
        }
    }

    if (indices_dirty) {
        indices_dirty = false;
        render_state.set_buffer(*indices.get());
    }
}
