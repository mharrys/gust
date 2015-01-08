#include "viewport.hpp"

#include "resolution.hpp"

gst::Viewport::Viewport()
    : Viewport(0, 0)
{
}

gst::Viewport::Viewport(Resolution resolution)
    : Viewport(0, 0, resolution.get_width(), resolution.get_height())
{
}

gst::Viewport::Viewport(unsigned int width, unsigned int height)
    : Viewport(0, 0, width, height)
{
}

gst::Viewport::Viewport(int x, int y, unsigned int width, unsigned int height)
    : x(x),
      y(y),
      width(width),
      height(height)
{
}

bool gst::Viewport::operator==(Viewport const & other)
{
    return x == other.x && y == other.y && width == other.width && height == other.height;
}

bool gst::Viewport::operator!=(Viewport const & other)
{
    return !(*this == other);
}

int gst::Viewport::get_x() const
{
    return x;
}

int gst::Viewport::get_y() const
{
    return y;
}

int gst::Viewport::get_width() const
{
    return width;
}

int gst::Viewport::get_height() const
{
    return height;
}
