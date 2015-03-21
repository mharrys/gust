#ifndef VERTEXARRAYIMPL_HPP_INCLUDED
#define VERTEXARRAYIMPL_HPP_INCLUDED

#include "vertexarray.hpp"

namespace gst
{
    class VertexArrayImpl : public VertexArray {
    public:
        void set_index_buffer(std::shared_ptr<IndexBuffer> buffer);
        void add_vertex_buffer(std::shared_ptr<VertexBuffer> buffer);
        void set_vertex_buffer(std::vector<std::shared_ptr<VertexBuffer>> buffers);
        std::vector<VertexBuffer *> get_vertex_buffers();
        IndexBuffer & get_index_buffer();
    private:
        std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers;
        std::shared_ptr<IndexBuffer> index_buffer;
    };
}

#endif
