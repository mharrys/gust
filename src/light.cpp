#include "light.hpp"

#include "shadoweddata.hpp"
#include "uniformmap.hpp"

gst::Light::Light(std::shared_ptr<UniformMap> uniforms)
    : uniforms(uniforms),
      enabled(true)
{
}

gst::ShadowedData & gst::Light::operator[](std::string const & annotation)
{
    return uniforms->get_uniform(annotation);
}

void gst::Light::set_enabled(bool enabled)
{
    this->enabled = enabled;
}

bool gst::Light::get_enabled() const
{
    return enabled;
}

gst::UniformMap & gst::Light::get_uniforms()
{
    return *uniforms;
}
