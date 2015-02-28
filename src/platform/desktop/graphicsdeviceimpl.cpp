#include "graphicsdeviceimpl.hpp"

#include "color.hpp"
#include "image.hpp"
#include "shadoweddata.hpp"
#include "viewport.hpp"

void gst::GraphicsDeviceImpl::clear(bool color, bool depth)
{
    int mask = 0;
    mask |= color ? GL_COLOR_BUFFER_BIT : 0;
    mask |= depth ? GL_DEPTH_BUFFER_BIT : 0;
    glClear(mask);
}

void gst::GraphicsDeviceImpl::set_clear_color(Color const & clear_color)
{
    glClearColor(
        clear_color.get_red(),
        clear_color.get_green(),
        clear_color.get_blue(),
        clear_color.get_alpha()
    );
}

void gst::GraphicsDeviceImpl::set_blend_mode(BlendMode blend_mode)
{
    if (blend_mode == BlendMode::NONE) {
        glDisable(GL_BLEND);
    } else {
        glEnable(GL_BLEND);
        switch (blend_mode) {
        case BlendMode::NONE:
            break;
        case BlendMode::ADDITIVE:
            glBlendFunc(GL_ONE, GL_ONE);
            break;
        case BlendMode::MULTIPLICATIVE:
            glBlendFunc(GL_DST_COLOR, GL_ZERO);
            break;
        case BlendMode::INTERPOLATIVE:
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            break;
        }
    }
}

void gst::GraphicsDeviceImpl::set_cull_face(CullFace cull_face)
{
    if (cull_face == CullFace::NONE) {
        glDisable(GL_CULL_FACE);
    } else {
        glEnable(GL_CULL_FACE);
        glCullFace(translator.translate(cull_face));
    }
}

void gst::GraphicsDeviceImpl::set_depth_mask(bool depth_mask)
{
    glDepthMask(depth_mask ? GL_TRUE : GL_FALSE);
}

void gst::GraphicsDeviceImpl::set_depth_test(bool depth_test)
{
    if (depth_test) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void gst::GraphicsDeviceImpl::set_viewport(Viewport const & viewport)
{
    glViewport(
        viewport.get_x(),
        viewport.get_y(),
        viewport.get_width(),
        viewport.get_height()
    );
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

gst::ResourceName gst::GraphicsDeviceImpl::create_renderbuffer()
{
    ResourceName name;
    glGenRenderbuffers(1, &name);
    return name;
}

void gst::GraphicsDeviceImpl::destroy_renderbuffer(ResourceName name)
{
    glDeleteRenderbuffers(1, &name);
}

void gst::GraphicsDeviceImpl::bind_renderbuffer(ResourceName name)
{
    glBindRenderbuffer(GL_RENDERBUFFER, name);
}

void gst::GraphicsDeviceImpl::renderbuffer_storage(Resolution size, RenderbufferFormat format)
{
    glRenderbufferStorage(GL_RENDERBUFFER, translator.translate(format), size.get_width(), size.get_height());
}

gst::ResourceName gst::GraphicsDeviceImpl::create_texture()
{
    ResourceName name;
    glGenBuffers(1, &name);
    return name;
}

void gst::GraphicsDeviceImpl::destroy_texture(ResourceName name)
{
    glDeleteTextures(1, &name);
}

void gst::GraphicsDeviceImpl::bind_texture(ResourceName name, TextureTarget target, int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(translator.translate(target), name);
}

void gst::GraphicsDeviceImpl::texture_image_2d(TextureTarget target, Image const & image, TextureParam const & param)
{
    auto size = image.get_size();

    glTexImage2D(
        translator.translate(target),
        0,
        translator.translate(param.internal_format),
        size.get_width(),
        size.get_height(),
        0,
        translator.translate(param.source_format),
        GL_UNSIGNED_BYTE,
        &image.get_data()[0]
    );
}

void gst::GraphicsDeviceImpl::texture_parameters(TextureTarget target, TextureParam const & param)
{
    auto tex_target = translator.translate(target);
    auto min_filter = translator.translate(param.min_filter);
    auto mag_filter = translator.translate(param.mag_filter);
    auto wrap_s = translator.translate(param.wrap_s);
    auto wrap_t = translator.translate(param.wrap_t);
    auto depth_compare = translator.translate(param.depth_compare);

    glTexParameteri(tex_target, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(tex_target, GL_TEXTURE_MAG_FILTER, mag_filter);
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_T, wrap_t);
    if (depth_compare == -1) {
        glTexParameteri(tex_target, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    } else {
        glTexParameteri(tex_target, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(tex_target, GL_TEXTURE_COMPARE_FUNC, depth_compare);
    }
}

gst::ResourceName gst::GraphicsDeviceImpl::create_framebuffer()
{
    ResourceName name;
    glGenFramebuffers(1, &name);
    return name;
}

void gst::GraphicsDeviceImpl::destroy_framebuffer(ResourceName name)
{
    glDeleteFramebuffers(1, &name);
}

void gst::GraphicsDeviceImpl::bind_framebuffer(ResourceName name)
{
    glBindFramebuffer(GL_FRAMEBUFFER, name);
}

void gst::GraphicsDeviceImpl::framebuffer_texture_2d(ResourceName name)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, name, 0);

    GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, draw_buffers);
}

void gst::GraphicsDeviceImpl::framebuffer_renderbuffer(ResourceName name)
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, name);
}

std::vector<std::string> gst::GraphicsDeviceImpl::check_framebuffer_status() const
{
    std::vector<std::string> errors;

    auto status_str = [](GLenum status)
    {
        switch (status) {
        case GL_FRAMEBUFFER_UNDEFINED:
            return "GL_FRAMEBUFFER_UNDEFINED";
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            return "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT";
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            return "GL_FRAMEBUFFER_INCOMPELTE_MISSING_ATTACHMENT";
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            return "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            return "GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER";
        case GL_FRAMEBUFFER_UNSUPPORTED:
            return "GL_FRAMEBUFFER_UNSUPPORTED";
        case GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE:
            return "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
        case GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS:
            return "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
        default:
            return "GL: unknown framebuffer status code " + status;
        }
    };

    auto log_error = [&](std::string const & name, GLenum buffer)
    {
        GLenum status = glCheckFramebufferStatus(buffer);
        if (status != GL_FRAMEBUFFER_COMPLETE) {
            errors.push_back(name + ": " + status_str(status));
        }
    };

    log_error("GL_READ_FRAMEBUFFER", GL_READ_FRAMEBUFFER);
    log_error("GL_DRAW_FRAMEBUFFER", GL_DRAW_FRAMEBUFFER);

    return errors;
}

std::vector<std::string> gst::GraphicsDeviceImpl::get_errors() const
{
    std::vector<std::string> errors;

    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR) {
        switch (error) {
            case GL_INVALID_ENUM:
                errors.push_back("GL_INVALID_ENUM");
                break;
            case GL_INVALID_VALUE:
                errors.push_back("GL_INVALID_VALUE");
                break;
            case GL_INVALID_OPERATION:
                errors.push_back("GL_INVALID_OPERATION");
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                errors.push_back("GL_INVALID_FRAMEBUFFER_OPERATION");
                break;
            case GL_OUT_OF_MEMORY:
                errors.push_back("GL_OUT_OF_MEMORY");
                break;
            case GL_STACK_UNDERFLOW:
                errors.push_back("GL_STACK_UNDERFLOW");
                break;
            case GL_STACK_OVERFLOW:
                errors.push_back("GL_STACK_OVERFLOW");
                break;
            default:
                errors.push_back("GL: unknown error code " + error);
                break;
        }
    }

    return errors;
}
