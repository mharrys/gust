#include "uniformmap.hpp"

#include "annotationformatter.hpp"
#include "shadoweddataimpl.hpp"

gst::UniformMap::UniformMap(std::shared_ptr<AnnotationFormatter> formatter)
    : formatter(formatter)
{
}

gst::ShadowedData & gst::UniformMap::get_uniform(std::string const & annotation)
{
    if (uniforms.count(annotation) == 0) {
        uniforms[annotation] = std::make_shared<ShadowedDataImpl>();
    }
    return *uniforms.at(annotation);
}

std::vector<gst::UniformAnnotation> gst::UniformMap::get_uniforms() const
{
    return std::vector<UniformAnnotation>(uniforms.begin(), uniforms.end());
}

std::shared_ptr<gst::AnnotationFormatter> gst::UniformMap::get_formatter() const
{
    return formatter;
}
