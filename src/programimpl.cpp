#include "programimpl.hpp"

#include "annotationformatter.hpp"
#include "logger.hpp"
#include "shaderimpl.hpp"
#include "shadoweddata.hpp"
#include "vertexattribute.hpp"

#include <fstream>
#include <sstream>

gst::ProgramImpl gst::ProgramImpl::create_from_file(
    Logger & logger,
    std::string const & vs_path,
    std::string const & fs_path)
{
    auto vs = ShaderImpl::create_from_file(logger, ShaderType::VERTEX, vs_path);
    auto fs = ShaderImpl::create_from_file(logger, ShaderType::FRAGMENT, fs_path);
    auto vs_ptr = std::unique_ptr<Shader>(new ShaderImpl(vs));
    auto fs_ptr = std::unique_ptr<Shader>(new ShaderImpl(fs));
    return ProgramImpl::create_from_shader(std::move(vs_ptr), std::move(fs_ptr));
}

gst::ProgramImpl gst::ProgramImpl::create_from_shader(
    std::unique_ptr<Shader> vs,
    std::unique_ptr<Shader> fs)
{
    // default attributes
    std::vector<AttributeLocation> locations = {
        { AttributeIndex::POSITION,  "vertex_position"  },
        { AttributeIndex::NORMAL,    "vertex_normal"    },
        { AttributeIndex::COLOR,     "vertex_color"     },
        { AttributeIndex::TEX_COORD, "vertex_tex_coord" },
    };
    return ProgramImpl(std::move(vs), std::move(fs), locations);
}

gst::ProgramImpl::ProgramImpl(
    std::unique_ptr<Shader> vs,
    std::unique_ptr<Shader> fs,
    std::vector<AttributeLocation> attribute_locations)
    : vertex_shader(std::move(vs)),
      fragment_shader(std::move(fs)),
      attribute_locations(attribute_locations)
{
    needs_update();
}

void gst::ProgramImpl::merge_uniforms(UniformMap const & uniforms)
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
