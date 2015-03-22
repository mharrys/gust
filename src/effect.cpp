#include "effect.hpp"

#include "pass.hpp"
#include "shadoweddata.hpp"
#include "uniformmap.hpp"

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
