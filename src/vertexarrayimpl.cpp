#include "vertexarrayimpl.hpp"

void gst::VertexArrayImpl::set_index_buffer(std::shared_ptr<Buffer> buffer)
{
    index_buffer = buffer;
    needs_update();
}

void gst::VertexArrayImpl::add_vertex_buffer(std::shared_ptr<Buffer> buffer, VertexAttributes attributes)
{
    vertex_buffers.push_back({ buffer, attributes });
    needs_update();
}

std::vector<gst::VertexBuffer> gst::VertexArrayImpl::get_vertex_buffers() const
{
    return vertex_buffers;
}

std::shared_ptr<gst::Buffer> gst::VertexArrayImpl::get_index_buffer() const
{
    return index_buffer;
}
