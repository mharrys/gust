#include "material.hpp"

#include "annotationarray.hpp"
#include "annotationfree.hpp"
#include "annotationstruct.hpp"
#include "pass.hpp"
#include "shadoweddata.hpp"
#include "uniformmapimpl.hpp"

gst::Material gst::Material::create_free(std::shared_ptr<Pass> pass)
{
    auto formatter = std::unique_ptr<AnnotationFormatter>(new AnnotationFree());
    auto uniforms = std::make_shared<UniformMapImpl>(std::move(formatter));
    return Material(pass, uniforms);
}

gst::Material gst::Material::create_struct(std::shared_ptr<Pass> pass, std::string const & name)
{
    auto formatter = std::unique_ptr<AnnotationFormatter>(new AnnotationStruct(name));
    auto uniforms = std::make_shared<UniformMapImpl>(std::move(formatter));
    return Material(pass, uniforms);
}

gst::Material gst::Material::create_array(std::shared_ptr<Pass> pass, std::string const & name)
{
    auto formatter = std::unique_ptr<AnnotationFormatter>(new AnnotationArray(name));
    auto uniforms = std::make_shared<UniformMapImpl>(std::move(formatter));
    return Material(pass, uniforms);
}

gst::Material::Material(
    std::shared_ptr<Pass> pass,
    std::shared_ptr<UniformMap> uniforms)
    : pass(pass),
      uniforms(uniforms)
{
}

gst::Pass & gst::Material::get_pass()
{
    return *pass;
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
