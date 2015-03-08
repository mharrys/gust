#include "texture.hpp"

gst::Texture::Texture()
    : internal_format(TextureFormat::RGB),
      source_format(PixelFormat::RGB),
      min_filter(FilterMode::LINEAR),
      mag_filter(FilterMode::LINEAR),
      wrap_s(WrapMode::REPEAT),
      wrap_t(WrapMode::REPEAT),
      depth_compare(CompareFunc::NONE)
{
}

void gst::Texture::set_internal_format(TextureFormat internal_format)
{
    this->internal_format = internal_format;
    needs_update();
}

void gst::Texture::set_source_format(PixelFormat source_format)
{
    this->source_format = source_format;
    needs_update();
}

void gst::Texture::set_min_filter(FilterMode min_filter)
{
    this->min_filter = min_filter;
    needs_update();
}

void gst::Texture::set_mag_filter(FilterMode mag_filter)
{
    this->mag_filter = mag_filter;
    needs_update();
}

void gst::Texture::set_wrap_s(WrapMode wrap_s)
{
    this->wrap_s = wrap_s;
    needs_update();
}

void gst::Texture::set_wrap_t(WrapMode wrap_t)
{
    this->wrap_t = wrap_t;
    needs_update();
}

void gst::Texture::set_depth_compare(CompareFunc depth_compare)
{
    this->depth_compare = depth_compare;
    needs_update();
}

gst::TextureFormat gst::Texture::get_internal_format() const
{
    return internal_format;
}

gst::PixelFormat gst::Texture::get_source_format() const
{
    return source_format;
}

gst::FilterMode gst::Texture::get_min_filter() const
{
    return min_filter;
}

gst::FilterMode gst::Texture::get_mag_filter() const
{
    return mag_filter;
}

gst::WrapMode gst::Texture::get_wrap_s() const
{
    return wrap_s;
}

gst::WrapMode gst::Texture::get_wrap_t() const
{
    return wrap_t;
}

gst::CompareFunc gst::Texture::get_depth_compare() const
{
    return depth_compare;
}
