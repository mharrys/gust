#include "graphicsdeviceimpl.hpp"

#include "shadoweddata.hpp"

void gst::GraphicsDeviceImpl::clear(bool color, bool depth)
{
    int mask = 0;
    mask |= color ? GL_COLOR_BUFFER_BIT : 0;
    mask |= depth ? GL_DEPTH_BUFFER_BIT : 0;
    glClear(mask);
}

gst::ShaderHandle gst::GraphicsDeviceImpl::create_shader(ShaderType type)
{
    ShaderHandle shader;
    shader.name = glCreateShader(translator.translate(type));
    return shader;
}

void gst::GraphicsDeviceImpl::destroy_shader(ShaderHandle shader)
{
    glDeleteShader(shader.name);
}

void gst::GraphicsDeviceImpl::compile_shader(ShaderHandle shader, std::string const & source)
{
    char const * shader_source = source.c_str();
    // replace source code in shader
    glShaderSource(shader.name, 1, &shader_source, NULL);
    // compile current set source code in shader
    glCompileShader(shader.name);
}

bool gst::GraphicsDeviceImpl::get_compile_status(ShaderHandle shader)
{
    GLint status;
    glGetShaderiv(shader.name, GL_COMPILE_STATUS, &status);
    return status == GL_TRUE;
}

std::string gst::GraphicsDeviceImpl::get_compile_error(ShaderHandle shader)
{
    GLint log_len;
    glGetShaderiv(shader.name, GL_INFO_LOG_LENGTH, &log_len);

    std::vector<GLchar> log_info(log_len);
    glGetShaderInfoLog(shader.name, log_len, NULL, &log_info[0]);

    return std::string(log_info.begin(), log_info.end());
}

gst::ProgramHandle gst::GraphicsDeviceImpl::create_program()
{
    ProgramHandle program;
    program.name = glCreateProgram();
    return program;
}

void gst::GraphicsDeviceImpl::destroy_program(ProgramHandle program)
{
    glDeleteProgram(program.name);
}

void gst::GraphicsDeviceImpl::attach_shader(ProgramHandle program, ShaderHandle shader)
{
    glAttachShader(program.name, shader.name);
}

void gst::GraphicsDeviceImpl::detach_shader(ProgramHandle program, ShaderHandle shader)
{
    glDetachShader(program.name, shader.name);
}

void gst::GraphicsDeviceImpl::link_program(ProgramHandle program)
{
    glLinkProgram(program.name);
}

bool gst::GraphicsDeviceImpl::get_link_status(ProgramHandle program)
{
    GLint status;
    glGetProgramiv(program.name, GL_LINK_STATUS, &status);
    return status == GL_TRUE;
}

std::string gst::GraphicsDeviceImpl::get_link_error(ProgramHandle program)
{
    GLint log_len;
    glGetProgramiv(program.name, GL_INFO_LOG_LENGTH, &log_len);

    std::vector<GLchar> log_info(log_len);
    glGetProgramInfoLog(program.name, log_len, NULL, &log_info[0]);

    return std::string(log_info.begin(), log_info.end());
}

void gst::GraphicsDeviceImpl::bind_attribute_location(ProgramHandle program, int index, std::string const & name)
{
    glBindAttribLocation(program.name, index, name.c_str());
}

int gst::GraphicsDeviceImpl::get_uniform_location(ProgramHandle program, std::string const & name)
{
    return glGetUniformLocation(program.name, name.c_str());
}

void gst::GraphicsDeviceImpl::uniform_int(int location, int value)
{
    glUniform1i(location, value);
}

void gst::GraphicsDeviceImpl::uniform_float(int location, float value)
{
    glUniform1f(location, value);
}

void gst::GraphicsDeviceImpl::uniform_vec2(int location, glm::vec2 const & value)
{
    glUniform2f(location, value.x, value.y);
}

void gst::GraphicsDeviceImpl::uniform_vec3(int location, glm::vec3 const & value)
{
    glUniform3f(location, value.x, value.y, value.z);
}

void gst::GraphicsDeviceImpl::uniform_vec4(int location, glm::vec4 const & value)
{
    glUniform4f(location, value.x, value.y, value.z, value.w);
}

void gst::GraphicsDeviceImpl::uniform_int_array(int location, std::vector<int> const & value)
{
    glUniform1iv(location, value.size(), &value[0]);
}

void gst::GraphicsDeviceImpl::uniform_float_array(int location, std::vector<float> const & value)
{
    glUniform1fv(location, value.size(), &value[0]);
}

void gst::GraphicsDeviceImpl::uniform_matrix3(int location, int count, bool transpose, std::vector<float> const & value)
{
    glUniformMatrix3fv(location, count, transpose ? GL_TRUE : GL_FALSE, &value[0]);
}

void gst::GraphicsDeviceImpl::uniform_matrix4(int location, int count, bool transpose, std::vector<float> const & value)
{
    glUniformMatrix4fv(location, count, transpose ? GL_TRUE : GL_FALSE, &value[0]);
}

void gst::GraphicsDeviceImpl::use_program(ProgramHandle program)
{
    glUseProgram(program.name);
}

gst::BufferHandle gst::GraphicsDeviceImpl::create_buffer()
{
    BufferHandle buffer;
    glGenBuffers(1, &buffer.name);
    return buffer;
}

void gst::GraphicsDeviceImpl::destroy_buffer(BufferHandle buffer)
{
    glDeleteBuffers(1, &buffer.name);
}

void gst::GraphicsDeviceImpl::bind_buffer(BufferHandle buffer, BufferTarget target)
{
    glBindBuffer(translator.translate(target), buffer.name);
}

void gst::GraphicsDeviceImpl::buffer_data(BufferTarget target, ShadowedData const & data, DataUsage usage)
{
    // shadowed data stores its data in a vector and we just want a pointer to
    // the first element of that vector, that is why we do not care about
    // array data type and just pick float for all
    auto raw_data = data.get_float_array();
    glBufferData(translator.translate(target), data.get_size_bytes(), &raw_data[0], translator.translate(usage));
}

gst::VertexArrayHandle gst::GraphicsDeviceImpl::create_vertex_array()
{
    VertexArrayHandle vertex_array;
    glGenVertexArrays(1, &vertex_array.name);
    return vertex_array;
}

void gst::GraphicsDeviceImpl::destroy_vertex_array(VertexArrayHandle vertex_array)
{
    glDeleteVertexArrays(1, &vertex_array.name);
}

void gst::GraphicsDeviceImpl::bind_vertex_array(VertexArrayHandle vertex_array)
{
    glBindVertexArray(vertex_array.name);
}

void gst::GraphicsDeviceImpl::draw_arrays(DrawMode mode, int first, int count)
{
    glDrawArrays(translator.translate(mode), first, count);
}

void gst::GraphicsDeviceImpl::draw_elements(DrawMode mode, int count)
{
    glDrawElements(translator.translate(mode), count, GL_UNSIGNED_INT, 0);
}

void gst::GraphicsDeviceImpl::enable_vertex_attribute(VertexAttribute const & attribute)
{
    glEnableVertexAttribArray(attribute.get_index());
    glVertexAttribPointer(
        attribute.get_index(),
        attribute.get_components(),
        translator.translate(attribute.get_type()),
        attribute.get_normalized() ? GL_TRUE : GL_FALSE,
        attribute.get_stride_bytes(),
        (GLvoid const *)(attribute.get_offset_bytes())
    );
}

gst::RenderbufferHandle gst::GraphicsDeviceImpl::create_renderbuffer()
{
    RenderbufferHandle renderbuffer;
    glGenRenderbuffers(1, &renderbuffer.name);
    return renderbuffer;
}

void gst::GraphicsDeviceImpl::destroy_renderbuffer(RenderbufferHandle renderbuffer)
{
    glDeleteRenderbuffers(1, &renderbuffer.name);
}

void gst::GraphicsDeviceImpl::bind_renderbuffer(RenderbufferHandle renderbuffer)
{
    glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer.name);
}

void gst::GraphicsDeviceImpl::renderbuffer_storage(Resolution size, RenderbufferFormat format)
{
    glRenderbufferStorage(GL_RENDERBUFFER, translator.translate(format), size.get_width(), size.get_height());
}
