#include "vertexarrayimpl.hpp"

#include "indexbuffer.hpp"
#include "vertexbuffer.hpp"

void gst::VertexArrayImpl::set_index_buffer(std::shared_ptr<IndexBuffer> buffer)
{
    index_buffer = buffer;
    needs_update();
}

void gst::VertexArrayImpl::add_vertex_buffer(std::shared_ptr<VertexBuffer> buffer)
{
    vertex_buffers.push_back(buffer);
    needs_update();
}

void gst::VertexArrayImpl::set_vertex_buffer(std::vector<std::shared_ptr<VertexBuffer>> buffers)
{
    vertex_buffers = buffers;
    needs_update();
}

std::vector<gst::VertexBuffer *> gst::VertexArrayImpl::get_vertex_buffers()
{
    std::vector<VertexBuffer *> result;
    for (auto buffer : vertex_buffers) {
        result.push_back(buffer.get());
    }
    return result;
}

gst::IndexBuffer & gst::VertexArrayImpl::get_index_buffer()
{
    return *index_buffer;
}
