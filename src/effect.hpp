#ifndef EFFECT_HPP_INCLUDED
#define EFFECT_HPP_INCLUDED

#include "texture.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class AnnotationFormatter;
    class Technique;
    class UniformCollection;

    class Effect {
    public:
        std::shared_ptr<UniformCollection> uniforms;
        std::shared_ptr<AnnotationFormatter> formatter;
        std::vector<std::shared_ptr<Texture>> textures;
        std::vector<std::shared_ptr<Technique>> techniques;
    };
}

#endif
