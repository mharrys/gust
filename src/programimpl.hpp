#ifndef PROGRAMIMPL_HPP_INCLUDED
#define PROGRAMIMPL_HPP_INCLUDED

#include "program.hpp"

#include <unordered_map>

namespace gst
{
    class ProgramImpl : public Program {
    public:
        void attach(std::shared_ptr<Shader> shader) override;
        void set_attributes(std::vector<AttributeLocation> attribute_locations) override;
        void set_uniforms(std::shared_ptr<UniformCollection> collection) override;
        std::vector<std::shared_ptr<Shader>> get_shaders() const override;
        std::vector<AttributeLocation> get_attribute_locations() const override;
        std::vector<UniformAnnotation> get_uniforms() const override;
    private:
        std::vector<std::shared_ptr<Shader>> shaders;
        std::vector<AttributeLocation> attribute_locations;
        std::unordered_map<std::string, std::shared_ptr<ShadowedData>> uniforms;
    };
}

#endif
