#include "texture.hpp"

#include "textureimpl.hpp"

gst::Texture::Texture(
    Resolution size,
    std::vector<unsigned char> const & data,
    TextureParam const & param)
    : Texture({ size, data }, param)
{
}

gst::Texture::Texture(
    Image const & image,
    TextureParam const & param)
    : impl(std::make_shared<TextureImpl>(param.target)),
      image(image),
      param(param),
      image_dirty(true),
      param_dirty(true)
{
}

bool gst::Texture::operator==(Texture const & other)
{
    return impl == other.impl;
}

bool gst::Texture::operator!=(Texture const & other)
{
    return !(*this == other);
}

gst::Texture::operator bool() const
{
    return impl != nullptr;
}

void gst::Texture::set_image(Resolution size, std::vector<unsigned char> const & data)
{
    set_image({ size, data });
}

void gst::Texture::set_image(Image const & image)
{
    this->image = image;
    image_dirty = true;
}

void gst::Texture::set_param(TextureParam const & param)
{
    this->param = param;
    param_dirty = true;
}

void gst::Texture::set_internal_format(TextureFormat internal_format)
{
    param.internal_format = internal_format;
    param_dirty = true;
}

void gst::Texture::set_source_format(PixelFormat source_format)
{
    param.source_format = source_format;
    param_dirty = true;
}

void gst::Texture::set_min_filter(FilterMode min_filter)
{
    param.min_filter = min_filter;
    param_dirty = true;
}

void gst::Texture::set_mag_filter(FilterMode mag_filter)
{
    param.mag_filter = mag_filter;
    param_dirty = true;
}

void gst::Texture::set_wrap_s(WrapMode wrap_s)
{
    param.wrap_s = wrap_s;
    param_dirty = true;
}

void gst::Texture::set_wrap_t(WrapMode wrap_t)
{
    param.wrap_t = wrap_t;
    param_dirty = true;
}

void gst::Texture::set_depth_compare(CompareFunc depth_compare)
{
    param.depth_compare = depth_compare;
    param_dirty = true;
}

gst::Image gst::Texture::get_image() const
{
    return image;
}

gst::TextureParam gst::Texture::get_param() const
{
    return param;
}

gst::TextureFormat gst::Texture::get_internal_format() const
{
    return param.internal_format;
}

gst::PixelFormat gst::Texture::get_source_format() const
{
    return param.source_format;
}

gst::FilterMode gst::Texture::get_min_filter() const
{
    return param.min_filter;
}

gst::FilterMode gst::Texture::get_mag_filter() const
{
    return param.mag_filter;
}

gst::WrapMode gst::Texture::get_wrap_s() const
{
    return param.wrap_t;
}

gst::WrapMode gst::Texture::get_wrap_t() const
{
    return param.wrap_t;
}

gst::CompareFunc gst::Texture::get_depth_compare() const
{
    return param.depth_compare;
}

void gst::Texture::refresh()
{
    if (param_dirty) {
        param_dirty = false;
        impl->parameter(param);
    }

    if (image_dirty) {
        image_dirty = false;
        impl->image2D(image);
    }
}
