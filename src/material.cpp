#include "material.hpp"

#include "annotationarray.hpp"
#include "annotationfree.hpp"
#include "annotationstruct.hpp"
#include "shadoweddata.hpp"
#include "uniformmapimpl.hpp"

gst::Material gst::Material::create_free()
{
    auto formatter = std::unique_ptr<AnnotationFormatter>(new AnnotationFree());
    auto uniforms = std::make_shared<UniformMapImpl>(std::move(formatter));
    return Material(uniforms);
}

gst::Material gst::Material::create_struct(std::string const & name)
{
    auto formatter = std::unique_ptr<AnnotationFormatter>(new AnnotationStruct(name));
    auto uniforms = std::make_shared<UniformMapImpl>(std::move(formatter));
    return Material(uniforms);
}

gst::Material::Material(std::shared_ptr<UniformMap> uniforms)
    : uniforms(uniforms)
{
}

gst::ShadowedData & gst::Material::get_uniform(std::string const & annotation)
{
    return uniforms->get_uniform(annotation);
}

gst::UniformMap & gst::Material::get_uniforms()
{
    return *uniforms;
}

gst::Textures & gst::Material::get_textures()
{
    return textures;
}
