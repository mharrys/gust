#ifndef VERTEXARRAY_HPP_INCLUDED
#define VERTEXARRAY_HPP_INCLUDED

#include "graphicsresource.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class IndexBuffer;
    class VertexBuffer;

    // The responsibility of this class is to mirror a vertex array object on
    // the graphics card.
    class VertexArray : public GraphicsResource {
    public:
        virtual ~VertexArray() = default;
        // Set index buffer.
        virtual void set_index_buffer(std::shared_ptr<IndexBuffer> buffer) = 0;
        // Add and enable vertex buffer.
        virtual void add_vertex_buffer(std::shared_ptr<VertexBuffer> buffer) = 0;
        // Set and enable vertex buffers. This will replace all existing
        // vertex buffers.
        virtual void set_vertex_buffer(std::vector<std::shared_ptr<VertexBuffer>> buffers) = 0;
        // Return vertex buffers.
        virtual std::vector<VertexBuffer *> get_vertex_buffers() = 0;
        // Return index buffer.
        virtual IndexBuffer * get_index_buffer() = 0;
    };
}

#endif
