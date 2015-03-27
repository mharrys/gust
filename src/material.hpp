#ifndef MATERIAL_HPP_INCLUDED
#define MATERIAL_HPP_INCLUDED

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

    // The responsibility of this class is to describe a material in a shader
    // pass.
    class Material {
    public:
        static Material create_free(std::shared_ptr<Pass> pass);
        static Material create_struct(std::shared_ptr<Pass> pass, std::string const & name);
        static Material create_array(std::shared_ptr<Pass> pass, std::string const & name);

        Material() = default;
        Material(
            std::shared_ptr<Pass> pass,
            std::shared_ptr<UniformMap> uniforms);

        // Return pass that renders this material.
        Pass & get_pass();
        // Return uniform.
        ShadowedData & get_uniform(std::string const & annotation);
        // Return uniforms that describe this material.
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
