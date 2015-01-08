#ifndef BUFFERIMPL_HPP_INCLUDED
#define BUFFERIMPL_HPP_INCLUDED

#include "translator.hpp"
#include "vertexattrib.hpp"

#include <cstdint>

namespace gst
{
    class RenderStateImpl;

    class BufferImpl {
        friend RenderStateImpl;
    public:
        BufferImpl(BufferTarget target);
        ~BufferImpl();
        void buffer_data(int64_t size, void const * data, DataUsage usage);
        void buffer_sub_data(int64_t offset, int64_t size, void const * data);
        void define(VertexAttrib const & attrib);
    private:
        void bind();

        GLuint id;
        GLenum target;

        Translator translator;
    };
}

#endif
