#ifndef PROGRAMIMPL_HPP_INCLUDED
#define PROGRAMIMPL_HPP_INCLUDED

#include "program.hpp"

#include <unordered_map>

namespace gst
{
    class ProgramImpl : public Program {
    public:
        void attach(std::shared_ptr<Shader> shader) final;
        void set_attributes(std::vector<AttributeLocation> attribute_locations) final;
        void set_uniforms(std::shared_ptr<UniformMap> collection) final;
        std::vector<std::shared_ptr<Shader>> get_shaders() const final;
        std::vector<AttributeLocation> get_attribute_locations() const final;
        std::vector<UniformAnnotation> get_uniforms() const final;
    private:
        std::vector<std::shared_ptr<Shader>> shaders;
        std::vector<AttributeLocation> attribute_locations;
        std::unordered_map<std::string, std::shared_ptr<ShadowedData>> uniforms;
    };
}

#endif
