#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "graphicsresource.hpp"

#include <vector>

namespace gst
{
    // Supported texture targets.
    enum class TextureTarget {
        TEXTURE_2D,
        TEXTURE_CUBE
    };

    // Supported texture formats.
    enum class TextureFormat {
        RGB,
        RGBA,
        RGBA16F,
        DEPTH_COMPONENT16,
        DEPTH_COMPONENT24,
        DEPTH_COMPONENT32,
        DEPTH_COMPONENT32F
    };

    // Supported pixel formats.
    enum class PixelFormat {
        RGB,
        RGBA,
        DEPTH_COMPONENT
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

    typedef std::vector<unsigned char> TextureData;

    // The responsibility of this class is to mirror a texture object on the
    // graphics card.
    class Texture : public GraphicsResource {
    public:
        Texture();
        virtual ~Texture() = default;
        // Set internal format.
        virtual void set_internal_format(TextureFormat internal_format);
        // Set source format.
        virtual void set_source_format(PixelFormat source_format);
        // Set minifying function.
        virtual void set_min_filter(FilterMode min_filter);
        // Set magnification function.
        virtual void set_mag_filter(FilterMode mag_filter);
        // Set wrap parameter for texture coordinate s.
        virtual void set_wrap_s(WrapMode wrap_s);
        // Set wrap parameter for texture coordinate t.
        virtual void set_wrap_t(WrapMode wrap_t);
        // Set wrap parameter for texture coordinate t.
        virtual void set_wrap_r(WrapMode wrap_t);
        // Set depth comparison function/operator.
        virtual void set_depth_compare(CompareFunc depth_compare);
        // Return texture target.
        virtual TextureTarget get_target() const = 0;
        // Return internal format.
        virtual TextureFormat get_internal_format() const;
        // Return source format.
        virtual PixelFormat get_source_format() const;
        // Return minifying function.
        virtual FilterMode get_min_filter() const;
        // Return magnification function.
        virtual FilterMode get_mag_filter() const;
        // Return wrap parameter for texture coordinate s.
        virtual WrapMode get_wrap_s() const;
        // Return wrap parameter for texture coordinate t.
        virtual WrapMode get_wrap_t() const;
        // Return wrap parameter for texture coordinate r.
        virtual WrapMode get_wrap_r() const;
        // Return depth comparison function/operator.
        virtual CompareFunc get_depth_compare() const;
    private:
        TextureFormat internal_format;
        PixelFormat source_format;
        FilterMode min_filter;
        FilterMode mag_filter;
        WrapMode wrap_s;
        WrapMode wrap_t;
        WrapMode wrap_r;
        CompareFunc depth_compare;
    };
}

#endif
