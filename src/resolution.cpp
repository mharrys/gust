#include "resolution.hpp"

gst::Resolution::Resolution()
    : Resolution(0, 0)
{
}

gst::Resolution::Resolution(unsigned int size)
    : width(size),
      height(size)
{
}

gst::Resolution::Resolution(unsigned int width, unsigned int height)
    : width(width),
      height(height)
{
}

bool gst::Resolution::operator==(Resolution const & other)
{
    return width == other.width && height == other.height;
}

bool gst::Resolution::operator!=(Resolution const & other)
{
    return !(*this == other);
}

unsigned int gst::Resolution::get_width() const
{
    return width;
}

unsigned int gst::Resolution::get_height() const
{
    return height;
}
