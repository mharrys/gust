#ifndef TEXTUREPARAM_HPP_INCLUDED
#define TEXTUREPARAM_HPP_INCLUDED

namespace gst
{
    // Supported texture targets.
    enum class TextureTarget {
        TEXTURE_2D
    };

    // Supported texture formats.
    enum class TextureFormat {
        RGB,
        RGBA,
        DEPTH_COMPONENT16,
        DEPTH_COMPONENT24,
        DEPTH_COMPONENT32,
        DEPTH_COMPONENT32F
    };

    // Supported pixel formats.
    enum class PixelFormat {
        RGB,
        RGBA
    };

    // Specifies texture filter mode.
    enum class FilterMode {
        NEAREST,
        LINEAR
    };

    // Specifies texture wrap mode.
    enum class WrapMode {
        CLAMP_TO_EDGE,
        MIRRORED_REPEAT,
        REPEAT
    };

    // Specifies comparison operator in texture compare mode.
    enum class CompareFunc {
        LEQUAL,
        GEQUAL,
        LESS,
        GREATER,
        EQUAL,
        NOTEQUAL,
        ALWAYS,
        NEVER,
        NONE
    };

    // The responsibility of this class is to act as a storage for texture
    // parameters and provide sensible default values.
    struct TextureParam {
        TextureParam();
        TextureFormat internal_format;
        PixelFormat source_format;
        FilterMode min_filter;
        FilterMode mag_filter;
        WrapMode wrap_s;
        WrapMode wrap_t;
        CompareFunc depth_compare;
    };
}

#endif
