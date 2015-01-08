#ifndef VERTEXARRAY_HPP_INCLUDED
#define VERTEXARRAY_HPP_INCLUDED

#include "glm.hpp"
#include "indexbuffer.hpp"
#include "vertexbuffer.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class RenderState;
    class VertexArrayImpl;

    enum class DrawMode {
        POINTS,
        LINE_STRIP,
        LINE_LOOP,
        LINES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
        TRIANGLES
    };

    class VertexArray {
        friend RenderState;
    public:
        VertexArray() = default;
        VertexArray(std::shared_ptr<RenderState> render_state);

        bool operator==(VertexArray const & other);
        bool operator!=(VertexArray const & other);
        explicit operator bool() const;

        void draw(DrawMode mode, int first, int count);
        void draw(DrawMode mode, int count, DataType type);

        template<typename T>
        void set(VertexBuffer<T> buffer)
        {
            push();
            buffer.use();
            pop();
        }

        template<typename T>
        void set(IndexBuffer<T> buffer)
        {
            push();
            buffer.use();
            pop();
        }
    private:
        void push();
        void pop();

        std::shared_ptr<VertexArrayImpl> impl;
        std::shared_ptr<RenderState> render_state;
    };
}

#endif
