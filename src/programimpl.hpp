#ifndef PROGRAMIMPL_HPP_INCLUDED
#define PROGRAMIMPL_HPP_INCLUDED

#include "program.hpp"

#include <unordered_map>

namespace gst
{
    class ProgramImpl : public Program {
    public:
        ProgramImpl() = default;
        void set_vertex_shader(std::unique_ptr<Shader> vertex_shader) final;
        void set_fragment_shader(std::unique_ptr<Shader> fragment_shader) final;
        void set_attributes(std::vector<AttributeLocation> attribute_locations) final;
        void set_uniforms(UniformMap const & uniforms) final;
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
