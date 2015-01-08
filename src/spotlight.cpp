#include "spotlight.hpp"

#include "lightvisitor.hpp"

gst::SpotLight::SpotLight()
    : SpotLight(UniformArrayLocation("spot_lights"))
{
}

gst::SpotLight::SpotLight(UniformArrayLocation location)
    : Light(location),
      ambient(0.0f),
      diffuse(1.0f),
      specular(1.0f),
      exponent(0.0f),
      cutoff(180.0f)
{
}

void gst::SpotLight::accept(LightVisitor & visitor)
{
    visitor.visit(*this);
}
