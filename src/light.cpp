#include "light.hpp"

gst::Light::Light(
    std::shared_ptr<UniformCollection> uniforms,
    std::shared_ptr<AnnotationFormatter> formatter)
    : uniforms(uniforms),
      formatter(formatter)
{
}

const std::shared_ptr<gst::UniformCollection> gst::Light::get_uniforms() const
{
    return uniforms;
}

const std::shared_ptr<gst::AnnotationFormatter> gst::Light::get_formatter() const
{
    return formatter;
}
