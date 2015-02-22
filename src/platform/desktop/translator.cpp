#include "translator.hpp"

GLenum gst::Translator::translate(TextureTarget target) const
{
    switch (target) {
    case TextureTarget::TEXTURE_2D:
        return GL_TEXTURE_2D;
    default:
        return 0;
    }
}

GLenum gst::Translator::translate(TextureFormat format) const
{
    switch (format) {
    case TextureFormat::RGB:
        return GL_RGB;
    case TextureFormat::RGBA:
        return GL_RGBA;
    case TextureFormat::DEPTH_COMPONENT16:
        return GL_DEPTH_COMPONENT16;
    case TextureFormat::DEPTH_COMPONENT24:
        return GL_DEPTH_COMPONENT24;
    case TextureFormat::DEPTH_COMPONENT32:
        return GL_DEPTH_COMPONENT32;
    case TextureFormat::DEPTH_COMPONENT32F:
        return GL_DEPTH_COMPONENT32F;
    default:
        return 0;
    }
}

GLenum gst::Translator::translate(PixelFormat format) const
{
    switch (format) {
    case PixelFormat::RGB:
        return GL_RGB;
    case PixelFormat::RGBA:
        return GL_RGBA;
    default:
        return 0;
    }
}

GLint gst::Translator::translate(FilterMode mode) const
{
    switch (mode) {
    case FilterMode::NEAREST:
        return GL_NEAREST;
    case FilterMode::LINEAR:
        return GL_LINEAR;
    default:
        return 0;
    }
}

GLint gst::Translator::translate(WrapMode mode) const
{
    switch(mode) {
    case WrapMode::CLAMP_TO_EDGE:
         return GL_CLAMP_TO_EDGE;
    case WrapMode::MIRRORED_REPEAT:
         return GL_MIRRORED_REPEAT;
    case WrapMode::REPEAT:
         return GL_REPEAT;
    default:
         return 0;
    }
}

GLenum gst::Translator::translate(RenderbufferFormat format) const
{
    switch (format) {
    case RenderbufferFormat::DEPTH_COMPONENT16:
        return GL_DEPTH_COMPONENT16;
    case RenderbufferFormat::DEPTH_COMPONENT24:
        return GL_DEPTH_COMPONENT24;
    case RenderbufferFormat::DEPTH_COMPONENT32:
        return GL_DEPTH_COMPONENT32;
    case RenderbufferFormat::DEPTH_COMPONENT32F:
        return GL_DEPTH_COMPONENT32F;
    default:
        return 0;
    }
}

GLenum gst::Translator::translate(DrawMode mode) const
{
    switch (mode) {
    case DrawMode::POINTS:
        return GL_POINTS;
    case DrawMode::LINE_STRIP:
        return GL_LINE_STRIP;
    case DrawMode::LINE_LOOP:
        return GL_LINE_LOOP;
    case DrawMode::LINES:
        return GL_LINES;
    case DrawMode::TRIANGLE_STRIP:
        return GL_TRIANGLE_STRIP;
    case DrawMode::TRIANGLE_FAN:
        return GL_TRIANGLE_FAN;
    case DrawMode::TRIANGLES:
        return GL_TRIANGLES;
    default:
        return 0;
    }
}

GLenum gst::Translator::translate(BufferTarget target) const
{
    switch (target) {
    case BufferTarget::ARRAY:
        return GL_ARRAY_BUFFER;
    case BufferTarget::ELEMENT_ARRAY:
        return GL_ELEMENT_ARRAY_BUFFER;
    default:
        return 0;
    }
}

GLenum gst::Translator::translate(VertexDataType type) const
{
    switch (type) {
    case VertexDataType::INT:
        return GL_INT;
    case VertexDataType::UNSIGNED_INT:
        return GL_UNSIGNED_INT;
    case VertexDataType::FLOAT:
        return GL_FLOAT;
    default:
        return 0;
    }
}

GLenum gst::Translator::translate(DataUsage usage) const
{
    switch (usage) {
    case DataUsage::STATIC:
        return GL_STATIC_DRAW;
    case DataUsage::DYNAMIC:
        return GL_DYNAMIC_DRAW;
    default:
        return 0;
    }
}

GLenum gst::Translator::translate(ShaderType type) const
{
    switch (type) {
    case ShaderType::VERTEX:
        return GL_VERTEX_SHADER;
    case ShaderType::FRAGMENT:
        return GL_FRAGMENT_SHADER;
    default:
        return 0;
    }
}

GLenum gst::Translator::translate(CullFace cull_face) const
{
    switch (cull_face) {
    case CullFace::FRONT:
        return GL_FRONT;
    case CullFace::BACK:
        return GL_BACK;
    case CullFace::FRONT_AND_BACK:
        return GL_FRONT_AND_BACK;
    default:
        return 0;
    }
}

GLint gst::Translator::translate(CompareFunc compare_func) const
{
    switch (compare_func) {
    case CompareFunc::LEQUAL:
        return GL_LEQUAL;
    case CompareFunc::GEQUAL:
        return GL_GEQUAL;
    case CompareFunc::LESS:
        return GL_LESS;
    case CompareFunc::GREATER:
        return GL_GREATER;
    case CompareFunc::EQUAL:
        return GL_EQUAL;
    case CompareFunc::NOTEQUAL:
        return GL_NOTEQUAL;
    case CompareFunc::ALWAYS:
        return GL_ALWAYS;
    case CompareFunc::NEVER:
        return GL_NEVER;
    case CompareFunc::NONE:
        return -1;
    default:
        return 0;
    }
}
