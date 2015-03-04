#ifndef VERTEXARRAY_HPP_INCLUDED
#define VERTEXARRAY_HPP_INCLUDED

#include "graphicsresource.hpp"
#include "vertexattribute.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Buffer;

    // Primitives to render.
    enum class DrawMode {
        POINTS,
        LINE_STRIP,
        LINE_LOOP,
        LINES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
        TRIANGLES
    };

    typedef std::vector<VertexAttribute> VertexAttributes;
    typedef std::pair<std::shared_ptr<Buffer>, VertexAttributes> VertexBuffer;

    // The responsibility of this class is to mirror a vertex array object on
    // the graphics card.
    class VertexArray : public GraphicsResource {
    public:
        virtual ~VertexArray() = default;
        // Set and enable index buffer.
        virtual void set_index_buffer(std::shared_ptr<Buffer> buffer) = 0;
        // Add and enable vertex buffer.
        virtual void add_vertex_buffer(std::shared_ptr<Buffer> buffer, VertexAttributes attributes) = 0;
        // Return added vertex buffers.
        virtual std::vector<VertexBuffer> get_vertex_buffers() const = 0;
        // Return set index buffer.
        virtual std::shared_ptr<Buffer> get_index_buffer() const = 0;
    };
}

#endif
