#include "program.hpp"

#include "logger.hpp"
#include "programimpl.hpp"
#include "shader.hpp"
#include "uniform.hpp"
#include "uniformarrayelement.hpp"
#include "uniformgroup.hpp"
#include "vertexattribute.hpp"

gst::Program::Program(
    std::shared_ptr<Logger> logger,
    std::vector<Shader> shaders,
    std::vector<AttributeLocation> const & locations)
    : impl(std::make_shared<ProgramImpl>()),
      logger(logger)
{
    for (auto & shader : shaders) {
        impl->attach(*shader.impl.get());
    }

    if (locations.empty()) {
        // default
        impl->bind_attrib_location(AttributeIndex::POSITION,  "vertex_position");
        impl->bind_attrib_location(AttributeIndex::NORMAL,    "vertex_normal");
        impl->bind_attrib_location(AttributeIndex::COLOR,     "vertex_color");
        impl->bind_attrib_location(AttributeIndex::TEX_COORD, "vertex_tex_coord");
    } else {
        // custom
        for (auto location : locations) {
            impl->bind_attrib_location(location.first, location.second);
        }
    }

    if (!impl->link()) {
        logger->log(TRACE("could not link program: " + impl->get_error_log()));
    }

    for (auto & shader : shaders) {
        impl->detach(*shader.impl.get());
    }
}

bool gst::Program::operator==(Program const & other)
{
    return impl == other.impl;
}

bool gst::Program::operator!=(Program const & other)
{
    return !(*this == other);
}

gst::Program::operator bool() const
{
    return impl != nullptr;
}

void gst::Program::update(std::string const & name, Uniform const & uniform)
{
    if (!uniform.shadowed_data) {
        logger->log(TRACE("attempted to update uniform \"" + name + "\" with no allocated data"));
        return;
    }

    int l = location(name);
    float * data;

    switch (uniform.type) {
    case UniformType::BOOL:
        impl->uniform1i(l, *std::static_pointer_cast<bool>(uniform.shadowed_data).get());
        break;
    case UniformType::INT:
        impl->uniform1i(l, *std::static_pointer_cast<int>(uniform.shadowed_data).get());
        break;
    case UniformType::FLOAT:
        impl->uniform1f(l, *std::static_pointer_cast<float>(uniform.shadowed_data).get());
        break;
    case UniformType::FLOAT_ARRAY:
        data = std::static_pointer_cast<float>(uniform.shadowed_data).get();
        impl->uniform1fv(l, uniform.count, data);
        break;
    case UniformType::VEC2:
        data = std::static_pointer_cast<float>(uniform.shadowed_data).get();
        impl->uniform2f(l, data[0], data[1]);
        break;
    case UniformType::VEC3:
        data = std::static_pointer_cast<float>(uniform.shadowed_data).get();
        impl->uniform3f(l, data[0], data[1], data[2]);
        break;
    case UniformType::VEC4:
        data = std::static_pointer_cast<float>(uniform.shadowed_data).get();
        impl->uniform4f(l, data[0], data[1], data[2], data[3]);
        break;
    case UniformType::MAT3:
        data = std::static_pointer_cast<float>(uniform.shadowed_data).get();
        impl->uniform_matrix3fv(l, 1, false, data);
        break;
    case UniformType::MAT4:
        data = std::static_pointer_cast<float>(uniform.shadowed_data).get();
        impl->uniform_matrix4fv(l, 1, false, data);
        break;
    }
}

void gst::Program::update(UniformArrayElement const & element)
{
    for (auto & uniform : element.uniforms) {
        update(element.get_array_name(uniform.first), uniform.second);
    }
}

void gst::Program::update(UniformGroup const & group)
{
    for (auto & uniform : group.uniforms) {
        update(group.get_name(uniform.first), uniform.second);
    }
}

int gst::Program::location(std::string const & name)
{
    if (uniforms.count(name) == 0) {
        uniforms[name] = impl->get_uniform_location(name);
        if (uniforms[name] == -1) {
            logger->log(TRACE("could not get uniform location for \"" + name + "\""));
        }
    }
    return uniforms.at(name);
}
