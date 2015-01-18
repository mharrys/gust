#ifndef EFFECT_HPP_INCLUDED
#define EFFECT_HPP_INCLUDED

#include "uniform.hpp"
#include "texture.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Technique;

    class Effect {
    public:
        std::vector<Uniform> uniforms;
        std::vector<Texture> textures;
        std::vector<std::shared_ptr<Technique>> techniques;
    };
}

#endif
