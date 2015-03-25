#ifndef EFFECT_HPP_INCLUDED
#define EFFECT_HPP_INCLUDED

#include <array>
#include <memory>
#include <string>
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
        static Effect create_free(std::shared_ptr<Pass> pass);
        static Effect create_struct(std::shared_ptr<Pass> pass, std::string const & name);
        static Effect create_array(std::shared_ptr<Pass> pass, std::string const & name);

        Effect() = default;
        Effect(
            std::shared_ptr<Pass> pass,
            std::shared_ptr<UniformMap> uniforms);

        // Return uniform associated with specified annotation.
        ShadowedData & operator[](std::string const & annotation);

        // Bind sampler with a unit and annotation.
        void bind_sampler(
            std::string const & annotation,
            std::shared_ptr<Texture> sampler,
            int unit);
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
