#ifndef EFFECT_HPP_INCLUDED
#define EFFECT_HPP_INCLUDED

#include <array>
#include <memory>
#include <vector>

namespace gst
{
    class Pass;
    class UniformMap;
    class ShadowedData;
    class Texture;

    typedef std::array<std::shared_ptr<Texture>, 5> Samplers;

    // The responsibility of this class is to describe a effect in a shader
    // pass.
    class Effect {
    public:
        Effect() = default;
        Effect(
            std::shared_ptr<Pass> pass,
            std::shared_ptr<UniformMap> uniforms);

        // Return uniform associated with specified annotation.
        ShadowedData & operator[](std::string const & annotation);

        // Return pass.
        Pass & get_pass();
        // Return uniforms.
        UniformMap & get_uniforms();
        // Return samplers.
        Samplers & get_samplers();
    private:
        std::shared_ptr<Pass> pass;
        std::shared_ptr<UniformMap> uniforms;
        Samplers samplers;
    };
}

#endif
