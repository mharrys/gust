#include "effect.hpp"

#include "annotationarray.hpp"
#include "annotationbasic.hpp"
#include "annotationstruct.hpp"
#include "pass.hpp"
#include "shadoweddata.hpp"
#include "uniformmapimpl.hpp"

gst::Effect gst::Effect::create_basic(std::shared_ptr<Pass> pass)
{
    auto formatter = std::make_shared<gst::AnnotationBasic>();
    auto uniforms = std::make_shared<gst::UniformMapImpl>(formatter);
    return Effect(pass, uniforms);
}

gst::Effect gst::Effect::create_struct(std::shared_ptr<Pass> pass, std::string const & name)
{
    auto formatter = std::make_shared<gst::AnnotationStruct>(name);
    auto uniforms = std::make_shared<gst::UniformMapImpl>(formatter);
    return Effect(pass, uniforms);
}

gst::Effect gst::Effect::create_array(std::shared_ptr<Pass> pass, std::string const & name)
{
    auto formatter = std::make_shared<gst::AnnotationArray>(name);
    auto uniforms = std::make_shared<gst::UniformMapImpl>(formatter);
    return Effect(pass, uniforms);
}

gst::Effect::Effect(
    std::shared_ptr<Pass> pass,
    std::shared_ptr<UniformMap> uniforms)
    : pass(pass),
      uniforms(uniforms)
{
}

gst::ShadowedData & gst::Effect::operator[](std::string const & annotation)
{
    return uniforms->get_uniform(annotation);
}

void gst::Effect::bind_sampler(
    std::string const & annotation,
    std::shared_ptr<Texture> sampler,
    int unit)
{
    uniforms->get_uniform(annotation) = unit;
    samplers[unit] = sampler;
}

gst::Pass & gst::Effect::get_pass()
{
    return *pass;
}

gst::UniformMap & gst::Effect::get_uniforms()
{
    return *uniforms;
}

gst::Samplers & gst::Effect::get_samplers()
{
    return samplers;
}
