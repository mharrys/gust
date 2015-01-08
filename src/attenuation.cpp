#include "attenuation.hpp"

gst::Attenuation::Attenuation()
    : Attenuation(1.0f, 0.0f, 0.0f)
{
}

gst::Attenuation::Attenuation(float constant, float linear, float quadratic)
    : constant(constant),
      linear(linear),
      quadratic(quadratic)
{
}

float gst::Attenuation::get_constant()
{
    return constant;
}

float gst::Attenuation::get_linear()
{
    return linear;
}

float gst::Attenuation::get_quadratic()
{
    return quadratic;
}
