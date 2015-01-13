#include "program.hpp"

#include "logger.hpp"
#include "programimpl.hpp"
#include "renderstate.hpp"
#include "shader.hpp"

gst::Program::Program(
    std::shared_ptr<RenderState> render_state,
    std::shared_ptr<Logger> logger,
    std::vector<Shader> shaders,
    std::vector<AttribLocation> const & locations)
    : impl(std::make_shared<ProgramImpl>()),
      render_state(render_state),
      logger(logger)
{
    for (auto & shader : shaders) {
        impl->attach(*shader.impl.get());
    }

    if (locations.empty()) {
        // default
        impl->bind_attrib_location(AttribIndex::POSITION,  "vertex_position");
        impl->bind_attrib_location(AttribIndex::NORMAL,    "vertex_normal");
        impl->bind_attrib_location(AttribIndex::COLOR,     "vertex_color");
        impl->bind_attrib_location(AttribIndex::TEX_COORD, "vertex_tex_coord");
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

void gst::Program::uniform(std::string const & name, bool value)
{
    push();
    impl->uniform1i(uniform(name), static_cast<int>(value));
    pop();
}

void gst::Program::uniform(std::string const & name, int value)
{
    push();
    impl->uniform1i(uniform(name), value);
    pop();
}

void gst::Program::uniform(std::string const & name, float value)
{
    push();
    impl->uniform1f(uniform(name), value);
    pop();
}

void gst::Program::uniform(std::string const & name, glm::mat3 const & value)
{
    push();
    impl->uniform_matrix3fv(uniform(name), 1, false, glm::value_ptr(value));
    pop();
}

void gst::Program::uniform(std::string const & name, glm::mat4 const & value)
{
    push();
    impl->uniform_matrix4fv(uniform(name), 1, false, glm::value_ptr(value));
    pop();
}

void gst::Program::uniform(std::string const & name, glm::vec2 const & value)
{
    push();
    impl->uniform2f(uniform(name), value[0], value[1]);
    pop();
}

void gst::Program::uniform(std::string const & name, glm::vec3 const & value)
{
    push();
    impl->uniform3f(uniform(name), value[0], value[1], value[2]);
    pop();
}

void gst::Program::uniform(std::string const & name, glm::vec4 const & value)
{
    push();
    impl->uniform4f(uniform(name), value[0], value[1], value[2], value[3]);
    pop();
}

void gst::Program::uniform(std::string const & name, std::vector<float> const & value)
{
    push();
    impl->uniform1fv(uniform(name), value.size(), &value[0]);
    pop();
}

int gst::Program::uniform(std::string const & name)
{
    if (uniforms.count(name) == 0) {
        uniforms[name] = impl->get_uniform_location(name);
        if (uniforms[name] == -1) {
            logger->log(TRACE("could not get uniform location for \"" + name + "\""));
        }
    }
    return uniforms.at(name);
}

void gst::Program::push()
{
    render_state->push();
    render_state->set_program(*this);
}

void gst::Program::pop()
{
    render_state->pop();
}
