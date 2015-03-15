#include "effect.hpp"

#include "pass.hpp"

gst::Effect::Effect(
    std::shared_ptr<Pass> pass,
    std::shared_ptr<UniformMap> uniforms)
    : pass(pass),
      uniforms(uniforms)
{
}

gst::Pass & gst::Effect::get_pass() const
{
    return *pass;
}

gst::UniformMap & gst::Effect::get_uniforms() const
{
    return *uniforms;
}

gst::EffectTextures & gst::Effect::get_textures()
{
    return textures;
}
