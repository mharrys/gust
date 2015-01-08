#include "distantlight.hpp"

#include "lightvisitor.hpp"

gst::DistantLight::DistantLight()
    : DistantLight(UniformArrayLocation("distant_lights"))
{
}

gst::DistantLight::DistantLight(UniformArrayLocation location)
    : Light(location),
      ambient(0.0f),
      diffuse(1.0f),
      specular(1.0f),
      direction(0.0f, 1.0f, 0.0f)
{
}

void gst::DistantLight::accept(LightVisitor & visitor)
{
    visitor.visit(*this);
}
