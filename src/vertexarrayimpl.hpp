#ifndef VERTEXARRAYIMPL_HPP_INCLUDED
#define VERTEXARRAYIMPL_HPP_INCLUDED

#include "vertexarray.hpp"

namespace gst
{
    class VertexArrayImpl : public VertexArray {
    public:
        void set_index_buffer(std::shared_ptr<Buffer> buffer);
        void add_vertex_buffer(std::shared_ptr<Buffer> buffer, VertexAttributes attributes);
        std::vector<VertexBuffer> get_vertex_buffers() const;
        std::shared_ptr<Buffer> get_index_buffer() const;
    private:
        std::vector<VertexBuffer> vertex_buffers;
        std::shared_ptr<Buffer> index_buffer;
    };
}

#endif
