#include "vertexarrayimpl.hpp"

#include "graphicsdevice.hpp"
#include "renderstate.hpp"

gst::VertexArrayImpl::VertexArrayImpl(std::shared_ptr<GraphicsDevice> device)
    : handle(device->create_vertex_array()),
      device(device),
      index_buffer_dirty(false),
      vertex_buffers_dirty(false)
{
}

gst::VertexArrayImpl::~VertexArrayImpl()
{
    device->destroy_vertex_array(handle);
}

void gst::VertexArrayImpl::draw_arrays(DrawMode mode, int first, int count)
{
    device->draw_arrays(mode, first, count);
}

void gst::VertexArrayImpl::draw_elements(DrawMode mode, int count)
{
    device->draw_elements(mode, count);
}

void gst::VertexArrayImpl::set_index_buffer(std::shared_ptr<Buffer> buffer)
{
    index_buffer = buffer;
    index_buffer_dirty = true;
}

void gst::VertexArrayImpl::add_vertex_buffer(std::shared_ptr<Buffer> buffer, VertexAttributes attributes)
{
    vertex_buffers.push_back({ buffer, attributes });
    vertex_buffers_dirty = true;
}

void gst::VertexArrayImpl::bind()
{
    device->bind_vertex_array(handle);
}

void gst::VertexArrayImpl::sync(RenderState & render_state)
{
    if (vertex_buffers_dirty) {
        vertex_buffers_dirty = false;
        for (auto vertex_buffer : vertex_buffers) {
            render_state.set_buffer(vertex_buffer.first);
            for (auto attribute : vertex_buffer.second) {
                device->enable_vertex_attribute(attribute);
            }
        }
    }

    if (index_buffer_dirty) {
        index_buffer_dirty = false;
        render_state.set_buffer(index_buffer);
    }
}
