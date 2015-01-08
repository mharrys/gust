#include "pointlight.hpp"

#include "lightvisitor.hpp"

gst::PointLight::PointLight()
    : PointLight(UniformArrayLocation("point_lights"))
{
}

gst::PointLight::PointLight(UniformArrayLocation location)
    : Light(location),
      ambient(0.0f),
      diffuse(1.0f),
      specular(1.0f)
{
}

void gst::PointLight::accept(LightVisitor & visitor)
{
    visitor.visit(*this);
}
