#ifndef VERTEXARRAY_HPP_INCLUDED
#define VERTEXARRAY_HPP_INCLUDED

#include "glm.hpp"
#include "indexbuffer.hpp"
#include "vertexbuffer.hpp"

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
        VertexArray();

        bool operator==(VertexArray const & other);
        bool operator!=(VertexArray const & other);
        explicit operator bool() const;

        void draw(DrawMode mode, int first, int count);
        void draw(DrawMode mode, int count, DataType type);

        void add(std::shared_ptr<VertexBuffer> vertices);
        void set(std::shared_ptr<IndexBuffer> indices);
    private:
        void refresh(RenderState & render_state);

        std::shared_ptr<VertexArrayImpl> impl;
        std::vector<std::shared_ptr<VertexBuffer>> vertex_buffers;
        std::shared_ptr<IndexBuffer> indices;
        bool vertices_dirty;
        bool indices_dirty;
    };
}

#endif
