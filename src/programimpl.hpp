#ifndef PROGRAMIMPL_HPP_INCLUDED
#define PROGRAMIMPL_HPP_INCLUDED

#include "program.hpp"

#include <unordered_map>

namespace gst
{
    class Logger;

    class ProgramImpl : public Program {
    public:
        // Construct program from shader files.
        static ProgramImpl create_from_file(
            Logger & logger,
            std::string const & vs_path,
            std::string const & fs_path);
        // Construct program from shaders.
        static ProgramImpl create_from_shader(
            std::unique_ptr<Shader> vs,
            std::unique_ptr<Shader> fs);
        // Construct empty program.
        ProgramImpl() = default;
        // Construct program from shaders and vertex attribute locations.
        ProgramImpl(
            std::unique_ptr<Shader> vs,
            std::unique_ptr<Shader> fs,
            std::vector<AttributeLocation> attribute_locations);
        void merge_uniforms(UniformMap const & uniforms) final;
        std::vector<Shader *> get_shaders() final;
        std::vector<AttributeLocation> get_attribute_locations() const final;
        std::vector<UniformAnnotation> get_uniforms() const final;
    private:
        std::unique_ptr<Shader> vertex_shader;
        std::unique_ptr<Shader> fragment_shader;
        std::vector<AttributeLocation> attribute_locations;
        std::unordered_map<std::string, std::shared_ptr<ShadowedData>> uniforms;
    };
}

#endif
