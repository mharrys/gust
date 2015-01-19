#include "light.hpp"

gst::Light::Light(std::string const & array_name)
    : uniforms(array_name)
{
}

gst::Light::Light(UniformArrayElement const & uniforms)
    : uniforms(uniforms)
{
}
