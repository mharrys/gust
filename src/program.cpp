#include "program.hpp"

#include "logger.hpp"
#include "programimpl.hpp"

gst::Program::Program(std::shared_ptr<ProgramImpl> impl, std::shared_ptr<Logger> logger)
    : impl(impl),
      logger(logger)
{
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
    impl->uniform1i(uniform(name), static_cast<int>(value));
}

void gst::Program::uniform(std::string const & name, int value)
{
    impl->uniform1i(uniform(name), value);
}

void gst::Program::uniform(std::string const & name, float value)
{
    impl->uniform1f(uniform(name), value);
}

void gst::Program::uniform(std::string const & name, glm::mat3 const & value)
{
    impl->uniform_matrix3fv(uniform(name), 1, false, glm::value_ptr(value));
}

void gst::Program::uniform(std::string const & name, glm::mat4 const & value)
{
    impl->uniform_matrix4fv(uniform(name), 1, false, glm::value_ptr(value));
}

void gst::Program::uniform(std::string const & name, glm::vec2 const & value)
{
    impl->uniform2f(uniform(name), value[0], value[1]);
}

void gst::Program::uniform(std::string const & name, glm::vec3 const & value)
{
    impl->uniform3f(uniform(name), value[0], value[1], value[2]);
}

void gst::Program::uniform(std::string const & name, glm::vec4 const & value)
{
    impl->uniform4f(uniform(name), value[0], value[1], value[2], value[3]);
}

void gst::Program::uniform(std::string const & name, std::vector<float> const & value)
{
    impl->uniform1fv(uniform(name), value.size(), &value[0]);
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
