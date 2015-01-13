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

float gst::Attenuation::get_constant() const
{
    return constant;
}

float gst::Attenuation::get_linear() const
{
    return linear;
}

float gst::Attenuation::get_quadratic() const
{
    return quadratic;
}
