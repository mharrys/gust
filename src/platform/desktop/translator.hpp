#ifndef TRANSLATOR_HPP_INCLUDED
#define TRANSLATOR_HPP_INCLUDED

#include "buffer.hpp"
#include "cullface.hpp"
#include "key.hpp"
#include "gl.hpp"
#include "shader.hpp"
#include "renderbufferformat.hpp"
#include "texture.hpp"
#include "vertexarray.hpp"

namespace gst
{
    class Translator {
    public:
        GLenum translate(TextureTarget target) const;
        GLenum translate(TextureFormat format) const;
        GLenum translate(PixelFormat format) const;
        GLint translate(FilterMode mode) const;
        GLint translate(WrapMode mode) const;
        GLenum translate(RenderbufferFormat format) const;
        GLenum translate(DrawMode mode) const;
        GLenum translate(BufferTarget target) const;
        GLenum translate(VertexDataType type) const;
        GLenum translate(DataUsage usage) const;
        GLenum translate(ShaderType type) const;
        GLenum translate(CullFace cull_face) const;
        GLint translate(CompareFunc compare_func) const;
    };
}

#endif
