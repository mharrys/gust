#include "color.hpp"

gst::Color::Color()
    : Color(0.0f, 0.0f, 0.0f, 1.0f)
{
}

gst::Color::Color(float red, float green, float blue, float alpha)
    : color(red, green, blue, alpha)
{
}

bool gst::Color::operator==(Color const & other) const
{
    return color == other.color;
}

bool gst::Color::operator!=(Color const & other) const
{
    return !(*this == other);
}

float gst::Color::get_red() const
{
    return color.x;
}

float gst::Color::get_green() const
{
    return color.y;
}

float gst::Color::get_blue() const
{
    return color.z;
}

float gst::Color::get_alpha() const
{
    return color.w;
}
