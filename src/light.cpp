#include "light.hpp"

#include "annotationarray.hpp"
#include "annotationfree.hpp"
#include "annotationstruct.hpp"
#include "shadoweddata.hpp"
#include "uniformmapimpl.hpp"

gst::Light gst::Light::create_free()
{
    auto formatter = std::unique_ptr<AnnotationFormatter>(new AnnotationFree());
    auto uniforms = std::make_shared<UniformMapImpl>(std::move(formatter));
    return Light(uniforms);
}

gst::Light gst::Light::create_struct(std::string const & name)
{
    auto formatter = std::unique_ptr<AnnotationFormatter>(new AnnotationStruct(name));
    auto uniforms = std::make_shared<UniformMapImpl>(std::move(formatter));
    return Light(uniforms);
}

gst::Light gst::Light::create_array(std::string const & name)
{
    auto formatter = std::unique_ptr<AnnotationFormatter>(new AnnotationArray(name));
    auto uniforms = std::make_shared<UniformMapImpl>(std::move(formatter));
    return Light(uniforms);
}

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
