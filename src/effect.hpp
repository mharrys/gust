#ifndef EFFECT_HPP_INCLUDED
#define EFFECT_HPP_INCLUDED

#include "texture.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Technique;
    class UniformMap;

    class Effect {
    public:
        std::shared_ptr<UniformMap> uniforms;
        std::vector<std::shared_ptr<Texture>> textures;
        std::vector<std::shared_ptr<Technique>> techniques;
    };
}

#endif
