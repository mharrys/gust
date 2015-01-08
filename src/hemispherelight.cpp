#include "hemispherelight.hpp"

#include "lightvisitor.hpp"

gst::HemisphereLight::HemisphereLight()
    : HemisphereLight(UniformArrayLocation("hemisphere_lights"))
{
}

gst::HemisphereLight::HemisphereLight(UniformArrayLocation location)
    : Light(location),
      upper(0.0f),
      lower(0.0f),
      direction(0.0f, 1.0f, 0.0f)
{
}

void gst::HemisphereLight::accept(LightVisitor & visitor)
{
    visitor.visit(*this);
}
