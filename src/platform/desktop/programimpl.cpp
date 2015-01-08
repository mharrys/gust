#include "programimpl.hpp"

#include "shaderimpl.hpp"

gst::ProgramImpl::ProgramImpl()
{
    id = glCreateProgram();
}

gst::ProgramImpl::~ProgramImpl()
{
    glDeleteProgram(id);
}

int gst::ProgramImpl::get_uniform_location(std::string const & name)
{
    return glGetUniformLocation(id, name.c_str());
}

void gst::ProgramImpl::uniform1i(int location, int v0)
{
    glUniform1i(location, v0);
}

void gst::ProgramImpl::uniform1f(int location, float v0)
{
    glUniform1f(location, v0);
}

void gst::ProgramImpl::uniform2f(int location, float v0, float v1)
{
    glUniform2f(location, v0, v1);
}

void gst::ProgramImpl::uniform3f(int location, float v0, float v1, float v2)
{
    glUniform3f(location, v0, v1, v2);
}

void gst::ProgramImpl::uniform4f(int location, float v0, float v1, float v2, float v3)
{
    glUniform4f(location, v0, v1, v2, v3);
}

void gst::ProgramImpl::uniform1fv(int location, int count, float const * value)
{
    glUniform1fv(location, count, value);
}

void gst::ProgramImpl::uniform_matrix3fv(int location, int count, bool transpose, float const * value)
{
    glUniformMatrix3fv(location, count, transpose ? GL_TRUE : GL_FALSE, value);
}

void gst::ProgramImpl::uniform_matrix4fv(int location, int count, bool transpose, float const * value)
{
    glUniformMatrix4fv(location, count, transpose ? GL_TRUE : GL_FALSE, value);
}

void gst::ProgramImpl::attach(ShaderImpl & shader)
{
    glAttachShader(id, shader.id);
}

void gst::ProgramImpl::detach(ShaderImpl & shader)
{
    glDetachShader(id, shader.id);
}

void gst::ProgramImpl::bind_attrib_location(int index, std::string const & name)
{
    glBindAttribLocation(id, index, name.c_str());
}

bool gst::ProgramImpl::link()
{
    glLinkProgram(id);

    GLint status;
    glGetProgramiv(id, GL_LINK_STATUS, &status);
    return status == GL_TRUE; // success if equal to GL_TRUE
}

std::string gst::ProgramImpl::get_error_log()
{
    GLint log_len;
    glGetProgramiv(id, GL_INFO_LOG_LENGTH, &log_len);

    std::vector<GLchar> log_info(log_len);
    glGetProgramInfoLog(id, log_len, NULL, &log_info[0]);

    return { log_info.begin(), log_info.end() };
}

void gst::ProgramImpl::use()
{
    glUseProgram(id);
}
