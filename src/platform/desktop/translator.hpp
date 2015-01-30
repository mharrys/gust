#ifndef TRANSLATOR_HPP_INCLUDED
#define TRANSLATOR_HPP_INCLUDED

#include "button.hpp"
#include "buffer.hpp"
#include "cullface.hpp"
#include "key.hpp"
#include "gl.hpp"
#include "sdl.hpp"
#include "shader.hpp"
#include "renderbuffer.hpp"
#include "textureparam.hpp"
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
        GLenum translate(DataType type) const;
        GLenum translate(DataUsage usage) const;
        GLenum translate(ShaderType type) const;
        GLenum translate(CullFace cull_face) const;
        GLint translate(CompareFunc compare_func) const;
        Button translate_button(int button) const;
        Key translate_key(int key) const;
    };
}

#endif
