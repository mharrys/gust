#ifndef MATERIAL_HPP_INCLUDED
#define MATERIAL_HPP_INCLUDED

#include <array>
#include <memory>
#include <string>
#include <vector>

namespace gst
{
    class UniformMap;
    class ShadowedData;
    class Texture;

    typedef std::array<std::shared_ptr<Texture>, 10> Textures;

    // The responsibility of this class is to describe a material in a shader
    // pass.
    class Material {
    public:
        // Construct material with a default uniform implementation using a
        // annotation formatter for free uniforms.
        static Material create_free();
        // Construct material with a default uniform implementation using a
        // annotation formatter for uniforms in a struct.
        static Material create_struct(std::string const & name);
        // Construct empty material.
        Material() = default;
        // Construct material from uniforms.
        Material(std::shared_ptr<UniformMap> uniforms);
        // Return uniform.
        ShadowedData & get_uniform(std::string const & annotation);
        // Return uniforms.
        UniformMap & get_uniforms();
        // Return textures.
        Textures & get_textures();
    private:
        std::shared_ptr<UniformMap> uniforms;
        Textures textures;
    };
}

#endif
