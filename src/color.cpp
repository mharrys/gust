#include "color.hpp"

gst::Color::Color()
    : Color(0.0f, 0.0f, 0.0f, 1.0f)
{
}

gst::Color::Color(float red, float green, float blue, float alpha)
    : rgba(red, green, blue, alpha)
{
}

bool gst::Color::operator==(Color const & other) const
{
    return rgba == other.rgba;
}

bool gst::Color::operator!=(Color const & other) const
{
    return !(*this == other);
}

float gst::Color::get_red() const
{
    return rgba.x;
}

float gst::Color::get_green() const
{
    return rgba.y;
}

float gst::Color::get_blue() const
{
    return rgba.z;
}

float gst::Color::get_alpha() const
{
    return rgba.w;
}
