#include "light.hpp"

#include "lightvisitor.hpp"

gst::Light::Light()
    : location("lights")
{
}

gst::Light::Light(UniformArrayLocation location)
    : location(location)
{
}

void gst::Light::accept(LightVisitor & visitor)
{
    visitor.visit(*this);
}
