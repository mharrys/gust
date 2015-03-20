#include "uniformmapimpl.hpp"

#include "annotationformatter.hpp"
#include "shadoweddataimpl.hpp"

gst::UniformMapImpl::UniformMapImpl(std::shared_ptr<AnnotationFormatter> formatter)
    : formatter(formatter)
{
}

gst::ShadowedData & gst::UniformMapImpl::get_uniform(std::string const & annotation)
{
    if (uniforms.count(annotation) == 0) {
        uniforms[annotation] = std::make_shared<ShadowedDataImpl>();
    }
    return *uniforms.at(annotation);
}

std::vector<gst::UniformAnnotation> gst::UniformMapImpl::get_uniforms() const
{
    return std::vector<UniformAnnotation>(uniforms.begin(), uniforms.end());
}

gst::AnnotationFormatter & gst::UniformMapImpl::get_formatter() const
{
    return *formatter;
}
