#ifndef VERTEXARRAYIMPL_HPP_INCLUDED
#define VERTEXARRAYIMPL_HPP_INCLUDED

#include "graphicsdevice.hpp"
#include "vertexarray.hpp"

namespace gst
{
    class GraphicsDevice;

    class VertexArrayImpl : public VertexArray {
    public:
        VertexArrayImpl(std::shared_ptr<GraphicsDevice> device);
        ~VertexArrayImpl();
        void draw_arrays(DrawMode mode, int first, int count);
        void draw_elements(DrawMode mode, int count);
        void set_index_buffer(std::shared_ptr<Buffer> buffer);
        void add_vertex_buffer(std::shared_ptr<Buffer> buffer, VertexAttributes attributes);
    private:
        void bind();
        void sync(RenderState & render_state);

        VertexArrayHandle handle;
        std::shared_ptr<GraphicsDevice> device;

        std::shared_ptr<Buffer> index_buffer;
        std::vector<VertexBuffer> vertex_buffers;
        bool index_buffer_dirty;
        bool vertex_buffers_dirty;
    };
}

#endif
