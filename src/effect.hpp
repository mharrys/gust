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

    typedef std::array<std::shared_ptr<Texture>, 10> Textures;

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

        // Return pass.
        Pass & get_pass();
        // Return uniform.
        ShadowedData & get_uniform(std::string const & annotation);
        // Return uniforms that describe this effect.
        UniformMap & get_uniforms();
        // Return textures.
        Textures & get_textures();
    private:
        std::shared_ptr<Pass> pass;
        std::shared_ptr<UniformMap> uniforms;
        Textures textures;
    };
}

#endif
