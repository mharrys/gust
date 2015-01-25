#ifndef VERTEXARRAYIMPL_HPP_INCLUDED
#define VERTEXARRAYIMPL_HPP_INCLUDED

#include "translator.hpp"

#include <memory>

namespace gst
{
    class RenderStateImpl;

    class VertexArrayImpl {
        friend RenderStateImpl;
    public:
        VertexArrayImpl();
        ~VertexArrayImpl();
        void draw_arrays(DrawMode mode, int first, int count) const;
        void draw_elements(DrawMode mode, int count, DataType type) const;
        void define(VertexAttribute const & attrib);
    private:
        void bind();

        GLuint id;
        Translator translator;
    };
}

#endif
