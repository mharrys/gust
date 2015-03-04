#include "programimpl.hpp"

#include "annotationformatter.hpp"
#include "shader.hpp"
#include "shadoweddata.hpp"

void gst::ProgramImpl::attach(std::shared_ptr<Shader> shader)
{
    shaders.push_back(shader);
    needs_update();
}

void gst::ProgramImpl::set_attributes(std::vector<AttributeLocation> attibute_locations)
{
    this->attribute_locations = attibute_locations;
    needs_update();
}

void gst::ProgramImpl::set_uniforms(std::shared_ptr<UniformCollection> collection)
{
    auto formatter = collection->get_formatter();
    for (auto uniform : collection->get_uniforms()) {
        uniforms[formatter->format(uniform.first)] = uniform.second;
    }
    needs_update();
}

std::vector<std::shared_ptr<gst::Shader>> gst::ProgramImpl::get_shaders() const
{
    return shaders;
}

std::vector<gst::AttributeLocation> gst::ProgramImpl::get_attribute_locations() const
{
    return attribute_locations;
}

std::vector<gst::UniformAnnotation> gst::ProgramImpl::get_uniforms() const
{
    return std::vector<UniformAnnotation>(uniforms.begin(), uniforms.end());
}
