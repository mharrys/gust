#include "image.hpp"

#include "shadoweddata.hpp"

gst::Image::Image(
    Resolution size,
    unsigned int components,
    std::unique_ptr<ShadowedData> data)
    : size(size),
      components(components),
      data(std::move(data))
{
}

gst::Resolution gst::Image::get_size() const
{
    return size;
}

unsigned int gst::Image::get_width() const
{
    return size.get_width();
}

unsigned int gst::Image::get_height() const
{
    return size.get_height();
}

unsigned int gst::Image::get_components() const
{
    return components;
}

gst::ShadowedData const & gst::Image::get_data() const
{
    return *data;
}

unsigned char const * gst::Image::get_uchar_pixels() const
{
    return static_cast<unsigned char const *>(data->get_data());
}

float const * gst::Image::get_float_pixels() const
{
    return static_cast<float const *>(data->get_data());
}
