#include "programimpl.hpp"

#include "annotationformatter.hpp"
#include "shader.hpp"
#include "shadoweddata.hpp"

void gst::ProgramImpl::set_vertex_shader(std::unique_ptr<Shader> vertex_shader)
{
    this->vertex_shader = std::move(vertex_shader);
    needs_update();
}

void gst::ProgramImpl::set_fragment_shader(std::unique_ptr<Shader> fragment_shader)
{
    this->fragment_shader = std::move(fragment_shader);
    needs_update();
}

void gst::ProgramImpl::set_attributes(std::vector<AttributeLocation> attibute_locations)
{
    this->attribute_locations = attibute_locations;
    needs_update();
}

void gst::ProgramImpl::set_uniforms(UniformMap const & uniforms)
{
    auto & formatter = uniforms.get_formatter();
    for (auto uniform : uniforms.get_uniforms()) {
        this->uniforms[formatter.format(uniform.first)] = uniform.second;
    }
    needs_update();
}

std::vector<gst::Shader *> gst::ProgramImpl::get_shaders()
{
    return { vertex_shader.get(), fragment_shader.get() };
}

std::vector<gst::AttributeLocation> gst::ProgramImpl::get_attribute_locations() const
{
    return attribute_locations;
}

std::vector<gst::UniformAnnotation> gst::ProgramImpl::get_uniforms() const
{
    return std::vector<UniformAnnotation>(uniforms.begin(), uniforms.end());
}
