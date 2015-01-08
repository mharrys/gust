#include "image.hpp"

gst::Image::Image(Resolution size, std::vector<unsigned char> const & data)
    : size(size),
      data(data)
{
}

gst::Resolution gst::Image::get_size() const
{
    return size;
}

std::vector<unsigned char> gst::Image::get_data() const
{
    return data;
}
