#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "image.hpp"
#include "resolution.hpp"
#include "textureparam.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Framebuffer;
    class RenderState;
    class TextureImpl;

    // TODO: Texture2D, TextureCube
    class Texture {
        friend Framebuffer;
        friend RenderState;
    public:
        Texture() = default;
        Texture(
            Resolution size,
            std::vector<unsigned char> const & data = {},
            TextureParam const & param = {});
        Texture(
            Image const & image,
            TextureParam const & param = {});

        bool operator==(Texture const & other);
        bool operator!=(Texture const & other);
        explicit operator bool() const;

        void set_image(Resolution size, std::vector<unsigned char> const & data = {});
        void set_image(Image const & image);
        void set_param(TextureParam const & param);
        void set_internal_format(TextureFormat internal_format);
        void set_source_format(PixelFormat source_format);
        void set_min_filter(FilterMode min_filter);
        void set_mag_filter(FilterMode mag_filter);
        void set_wrap_s(WrapMode wrap_s);
        void set_wrap_t(WrapMode wrap_t);

        Image get_image() const;
        TextureParam get_param() const;
        TextureFormat get_internal_format() const;
        PixelFormat get_source_format() const;
        FilterMode get_min_filter() const;
        FilterMode get_mag_filter() const;
        WrapMode get_wrap_s() const;
        WrapMode get_wrap_t() const;
    private:
        void refresh();

        std::shared_ptr<TextureImpl> impl;
        Image image;
        TextureParam param;
        bool image_dirty;
        bool param_dirty;
    };
}

#endif
