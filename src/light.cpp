#include "light.hpp"

gst::Light::Light(std::shared_ptr<UniformCollection> uniforms)
    : uniforms(uniforms)
{
}

std::shared_ptr<gst::UniformCollection> gst::Light::get_uniforms() const
{
    return uniforms;
}
