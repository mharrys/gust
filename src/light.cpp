#include "light.hpp"

gst::Light::Light(std::shared_ptr<UniformMap> uniforms)
    : uniforms(uniforms),
      enabled(true)
{
}

void gst::Light::set_enabled(bool enabled)
{
    this->enabled = enabled;
}

std::shared_ptr<gst::UniformMap> gst::Light::get_uniforms() const
{
    return uniforms;
}

bool gst::Light::get_enabled() const
{
    return enabled;
}
