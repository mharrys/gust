#ifndef TEXTUREPARAM_HPP_INCLUDED
#define TEXTUREPARAM_HPP_INCLUDED

namespace gst
{
    enum class TextureTarget {
        TEXTURE_2D
    };

    enum class TextureFormat {
        RGB,
        RGBA,
        DEPTH_COMPONENT16,
        DEPTH_COMPONENT24,
        DEPTH_COMPONENT32,
        DEPTH_COMPONENT32F
    };

    enum class PixelFormat {
        RGB,
        RGBA
    };

    enum class FilterMode {
        NEAREST,
        LINEAR
    };

    enum class WrapMode {
        CLAMP_TO_EDGE,
        MIRRORED_REPEAT,
        REPEAT
    };

    struct TextureParam {
        TextureParam();

        TextureTarget target;
        TextureFormat internal_format;
        PixelFormat source_format;
        FilterMode min_filter;
        FilterMode mag_filter;
        WrapMode wrap_s;
        WrapMode wrap_t;
    };
}

#endif
