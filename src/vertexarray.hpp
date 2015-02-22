#ifndef VERTEXARRAY_HPP_INCLUDED
#define VERTEXARRAY_HPP_INCLUDED

#include "vertexattribute.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Buffer;
    class RenderState;

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
    class VertexArray {
        friend RenderState;
    public:
        virtual ~VertexArray() = default;
        // Render primitives from stored array data.
        virtual void draw_arrays(DrawMode mode, int first, int count) = 0;
        // Render primitives from stored array data.
        virtual void draw_elements(DrawMode mode, int count) = 0;
        // Set and enable index buffer.
        virtual void set_index_buffer(std::shared_ptr<Buffer> buffer) = 0;
        // Add and enable vertex buffer.
        virtual void add_vertex_buffer(std::shared_ptr<Buffer> buffer, VertexAttributes attributes) = 0;
    protected:
        // Notify graphics card to bind this vertex array.
        virtual void bind() = 0;
        // Sync client state with graphics card.
        virtual void sync(RenderState & render_state) = 0;
    };
}

#endif
