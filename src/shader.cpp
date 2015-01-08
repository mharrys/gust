#include "shader.hpp"

#include "shaderimpl.hpp"

gst::Shader::Shader(ShaderType type, std::string const & source)
    : impl(std::make_shared<ShaderImpl>(type))
{
    compile_successful = impl->compile(source);
    if (!compile_successful) {
        error = impl->get_error_log();
    }
}

bool gst::Shader::operator==(Shader const & other)
{
    return impl == other.impl;
}

bool gst::Shader::operator!=(Shader const & other)
{
    return !(*this == other);
}

gst::Shader::operator bool() const
{
    return impl != nullptr && compile_successful;
}

std::string gst::Shader::get_compile_error() const
{
    return error;
}
