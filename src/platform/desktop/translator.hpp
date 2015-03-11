#ifndef TRANSLATOR_HPP_INCLUDED
#define TRANSLATOR_HPP_INCLUDED

#include "gl.hpp"

namespace gst
{
    enum class AttachmentPoint;
    enum class AttachmentType;
    enum class BufferTarget;
    enum class CubeFace;
    enum class CullFace;
    enum class CompareFunc;
    enum class DataUsage;
    enum class DrawMode;
    enum class FilterMode;
    enum class PixelFormat;
    enum class RenderbufferFormat;
    enum class ShaderType;
    enum class TextureFormat;
    enum class TextureTarget;
    enum class VertexDataType;
    enum class WrapMode;

    class Translator {
    public:
        GLenum translate(AttachmentPoint attachment_point) const;
        GLenum translate(AttachmentType attachment_type) const;
        GLenum translate(BufferTarget target) const;
        GLenum translate(CubeFace cube_face) const;
        GLenum translate(CullFace cull_face) const;
        GLint translate(CompareFunc compare_func) const;
        GLenum translate(DataUsage usage) const;
        GLenum translate(DrawMode mode) const;
        GLint translate(FilterMode mode) const;
        GLenum translate(PixelFormat format) const;
        GLenum translate(RenderbufferFormat format) const;
        GLenum translate(ShaderType type) const;
        GLenum translate(TextureFormat format) const;
        GLenum translate(TextureTarget target) const;
        GLenum translate(VertexDataType type) const;
        GLint translate(WrapMode mode) const;
    };
}

#endif
