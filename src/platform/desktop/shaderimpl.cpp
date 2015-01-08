#include "shaderimpl.hpp"

gst::ShaderImpl::ShaderImpl(ShaderType type)
    : source("")
{
    this->type = translator.translate(type);
    id = glCreateShader(this->type);
}

gst::ShaderImpl::~ShaderImpl()
{
    glDeleteShader(id);
}

bool gst::ShaderImpl::compile(std::string const & source)
{
    char const * shader_source = source.c_str();

    // replace source code in shader
    glShaderSource(id, 1, &shader_source, NULL);
    // compile the source code now set in shader
    glCompileShader(id);

    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    return status == GL_TRUE; // success if equal to GL_TRUE
}

std::string gst::ShaderImpl::get_error_log()
{
    GLint log_len;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &log_len);

    std::vector<GLchar> log_info(log_len);
    glGetShaderInfoLog(id, log_len, NULL, &log_info[0]);

    return { log_info.begin(), log_info.end() };
}
