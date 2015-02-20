#ifndef VERTEXARRAY_HPP_INCLUDED
#define VERTEXARRAY_HPP_INCLUDED

namespace gst
{
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

    // The responsibility of this class is to mirror a vertex array object on
    // the graphics card.
    class VertexArray {
        friend RenderState;
    public:
        // Render primitives from stored array data.
        virtual void draw_arrays(DrawMode mode, int first, int count) = 0;
        // Render primitives from stored array data.
        virtual void draw_elements(DrawMode mode, int count) = 0;
    protected:
        // Notify graphics card to bind this vertex array.
        virtual void bind() = 0;
        // Sync client state with graphics card.
        virtual void sync(RenderState & render_state) = 0;
    };
}

#endif
