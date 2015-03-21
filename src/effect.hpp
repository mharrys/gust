#ifndef EFFECT_HPP_INCLUDED
#define EFFECT_HPP_INCLUDED

#include "texture.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Pass;
    class UniformMap;

    typedef std::vector<std::shared_ptr<Texture>> EffectTextures;

    // The responsibility of this class is to describe a effect for a shader
    // pass.
    class Effect {
    public:
        Effect() = default;
        Effect(
            std::shared_ptr<Pass> pass,
            std::shared_ptr<UniformMap> uniforms,
            EffectTextures const & textures = {});
        // Return pass.
        Pass & get_pass() const;
        // Return uniforms.
        UniformMap & get_uniforms() const;
        // Return textures.
        EffectTextures & get_textures();
    private:
        std::shared_ptr<Pass> pass;
        std::shared_ptr<UniformMap> uniforms;
        EffectTextures textures;
    };
}

#endif
