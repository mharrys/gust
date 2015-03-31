#include "graphicsdeviceimpl.hpp"

#include "buffer.hpp"
#include "blendmode.hpp"
#include "color.hpp"
#include "cullface.hpp"
#include "framebufferattachment.hpp"
#include "image.hpp"
#include "renderbuffer.hpp"
#include "shadoweddata.hpp"
#include "shader.hpp"
#include "texture.hpp"
#include "viewport.hpp"

void gst::GraphicsDeviceImpl::clear(bool color, bool depth)
{
    auto mask = 0;
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

gst::ResourceName gst::GraphicsDeviceImpl::create_shader(ShaderType type)
{
    return glCreateShader(translator.translate(type));
}

void gst::GraphicsDeviceImpl::destroy_shader(ResourceName name)
{
    glDeleteShader(name);
}

void gst::GraphicsDeviceImpl::compile_shader(ResourceName name, std::string const & source)
{
    auto const * shader_source = source.c_str();
    // replace source code in shader
    glShaderSource(name, 1, &shader_source, NULL);
    // compile current set source code in shader
    glCompileShader(name);
}

bool gst::GraphicsDeviceImpl::get_compile_status(ResourceName name)
{
    GLint status;
    glGetShaderiv(name, GL_COMPILE_STATUS, &status);
    return status == GL_TRUE;
}

std::string gst::GraphicsDeviceImpl::get_compile_error(ResourceName name)
{
    GLint log_len;
    glGetShaderiv(name, GL_INFO_LOG_LENGTH, &log_len);

    std::vector<GLchar> log_info(log_len);
    glGetShaderInfoLog(name, log_len, NULL, &log_info[0]);

    return std::string(log_info.begin(), log_info.end());
}

gst::ResourceName gst::GraphicsDeviceImpl::create_program()
{
    return glCreateProgram();
}

void gst::GraphicsDeviceImpl::destroy_program(ResourceName name)
{
    glDeleteProgram(name);
}

void gst::GraphicsDeviceImpl::attach_shader(ResourceName program_name, ResourceName shader_name)
{
    glAttachShader(program_name, shader_name);
}

void gst::GraphicsDeviceImpl::detach_shader(ResourceName program_name, ResourceName shader_name)
{
    glDetachShader(program_name, shader_name);
}

void gst::GraphicsDeviceImpl::link_program(ResourceName name)
{
    glLinkProgram(name);
}

bool gst::GraphicsDeviceImpl::get_link_status(ResourceName name)
{
    GLint status;
    glGetProgramiv(name, GL_LINK_STATUS, &status);
    return status == GL_TRUE;
}

std::string gst::GraphicsDeviceImpl::get_link_error(ResourceName name)
{
    GLint log_len;
    glGetProgramiv(name, GL_INFO_LOG_LENGTH, &log_len);

    std::vector<GLchar> log_info(log_len);
    glGetProgramInfoLog(name, log_len, NULL, &log_info[0]);

    return std::string(log_info.begin(), log_info.end());
}

void gst::GraphicsDeviceImpl::bind_attribute_location(ResourceName program_name, int index, std::string const & name)
{
    glBindAttribLocation(program_name, index, name.c_str());
}

int gst::GraphicsDeviceImpl::get_uniform_location(ResourceName program_name, std::string const & name)
{
    return glGetUniformLocation(program_name, name.c_str());
}

void gst::GraphicsDeviceImpl::uniform(int location, ShadowedData const & data)
{
    auto raw_data = data.get_data();
    auto raw_int  = static_cast<int const *>(raw_data);
    auto raw_uint = static_cast<unsigned int const *>(raw_data);
    auto raw_float = static_cast<float const *>(raw_data);

    switch (data.get_type()) {
    case DataType::NONE:
        // ignore
        break;
    case DataType::BOOL:
    case DataType::INT:
        glUniform1i(location, raw_int[0]);
        break;
    case DataType::UINT:
        glUniform1ui(location, raw_uint[0]);
        break;
    case DataType::FLOAT:
        glUniform1f(location, raw_float[0]);
        break;
    case DataType::VEC2:
        glUniform2f(location, raw_float[0], raw_float[1]);
        break;
    case DataType::VEC3:
        glUniform3f(location, raw_float[0], raw_float[1], raw_float[2]);
        break;
    case DataType::VEC4:
        glUniform4f(location, raw_float[0], raw_float[1], raw_float[2], raw_float[3]);
        break;
    case DataType::MAT3:
    case DataType::MAT3_ARRAY:
        glUniformMatrix3fv(location, data.get_count(), GL_FALSE, raw_float);
        break;
    case DataType::MAT4:
    case DataType::MAT4_ARRAY:
        glUniformMatrix4fv(location, data.get_count(), GL_FALSE, raw_float);
        break;
    case DataType::INT_ARRAY:
        glUniform1iv(location, data.get_count(), raw_int);
        break;
    case DataType::UCHAR_ARRAY:
    case DataType::UINT_ARRAY:
        glUniform1uiv(location, data.get_count(), raw_uint);
        break;
    case DataType::FLOAT_ARRAY:
        glUniform1fv(location, data.get_count(), raw_float);
        break;
    case DataType::VEC2_ARRAY:
        glUniform2fv(location, data.get_count(), raw_float);
        break;
    case DataType::VEC3_ARRAY:
        glUniform3fv(location, data.get_count(), raw_float);
        break;
    case DataType::VEC4_ARRAY:
        glUniform4fv(location, data.get_count(), raw_float);
        break;
    }
}

void gst::GraphicsDeviceImpl::use_program(ResourceName name)
{
    glUseProgram(name);
}

gst::ResourceName gst::GraphicsDeviceImpl::create_buffer()
{
    ResourceName name;
    glGenBuffers(1, &name);
    return name;
}

void gst::GraphicsDeviceImpl::destroy_buffer(ResourceName name)
{
    glDeleteBuffers(1, &name);
}

void gst::GraphicsDeviceImpl::bind_buffer(ResourceName name, BufferTarget target)
{
    glBindBuffer(translator.translate(target), name);
}

void gst::GraphicsDeviceImpl::buffer_data(BufferTarget target, ShadowedData const & data, DataUsage usage)
{
    glBufferData(translator.translate(target), data.get_size_bytes(), data.get_data(), translator.translate(usage));
}

gst::ResourceName gst::GraphicsDeviceImpl::create_vertex_array()
{
    ResourceName name;
    glGenVertexArrays(1, &name);
    return name;
}

void gst::GraphicsDeviceImpl::destroy_vertex_array(ResourceName name)
{
    glDeleteVertexArrays(1, &name);
}

void gst::GraphicsDeviceImpl::bind_vertex_array(ResourceName name)
{
    glBindVertexArray(name);
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
    glEnableVertexAttribArray(attribute.index);
    glVertexAttribPointer(
        attribute.index,
        attribute.components,
        translator.translate(attribute.type),
        GL_FALSE,
        attribute.stride_bytes,
        (GLvoid const *)(attribute.offset_bytes)
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

void gst::GraphicsDeviceImpl::update_texture_storage(
    TextureFormat internal_format,
    PixelFormat source_format,
    Resolution size,
    ShadowedData const & data)
{
    update_texture_storage(
        GL_TEXTURE_2D,
        translator.translate(internal_format),
        translator.translate(source_format),
        size.get_width(),
        size.get_height(),
        data
    );
}

void gst::GraphicsDeviceImpl::update_texture_storage(
    TextureFormat internal_format,
    PixelFormat source_format,
    Resolution size,
    ShadowedData const & data,
    CubeFace face)
{
    update_texture_storage(
        translator.translate(face),
        translator.translate(internal_format),
        translator.translate(source_format),
        size.get_width(),
        size.get_height(),
        data
    );
}

void gst::GraphicsDeviceImpl::update_texture_min_filter(TextureTarget target, FilterMode min_filter)
{
    const auto tex_target = translator.translate(target);
    const auto tex_min_filter = translator.translate(min_filter);
    glTexParameteri(tex_target, GL_TEXTURE_MIN_FILTER, tex_min_filter);
}

void gst::GraphicsDeviceImpl::update_texture_mag_filter(TextureTarget target, FilterMode mag_filter)
{
    const auto tex_target = translator.translate(target);
    const auto tex_mag_filter = translator.translate(mag_filter);
    glTexParameteri(tex_target, GL_TEXTURE_MAG_FILTER, tex_mag_filter);
}

void gst::GraphicsDeviceImpl::update_texture_wrap_s(TextureTarget target, WrapMode wrap_s)
{
    const auto tex_target = translator.translate(target);
    const auto tex_wrap_s = translator.translate(wrap_s);
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_S, tex_wrap_s);
}

void gst::GraphicsDeviceImpl::update_texture_wrap_t(TextureTarget target, WrapMode wrap_t)
{
    const auto tex_target = translator.translate(target);
    const auto tex_wrap_t = translator.translate(wrap_t);
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_T, tex_wrap_t);
}

void gst::GraphicsDeviceImpl::update_texture_wrap_r(TextureTarget target, WrapMode wrap_r)
{
    const auto tex_target = translator.translate(target);
    const auto tex_wrap_r = translator.translate(wrap_r);
    glTexParameteri(tex_target, GL_TEXTURE_WRAP_R, tex_wrap_r);
}

void gst::GraphicsDeviceImpl::update_texture_compare_func(TextureTarget target, CompareFunc compare_func)
{
    const auto tex_target = translator.translate(target);
    const auto tex_compare_func = translator.translate(compare_func);
    if (tex_compare_func == 0) {
        glTexParameteri(tex_target, GL_TEXTURE_COMPARE_MODE, GL_NONE);
    } else {
        glTexParameteri(tex_target, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
        glTexParameteri(tex_target, GL_TEXTURE_COMPARE_FUNC, tex_compare_func);
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

void gst::GraphicsDeviceImpl::attach_to_framebuffer(ResourceName attachment, AttachmentType type, AttachmentPoint point)
{
    const auto attachment_type = translator.translate(type);
    const auto attachment_point = translator.translate(point);

    if (type == AttachmentType::RENDERBUFFER) {
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, attachment_point, GL_RENDERBUFFER, attachment);
    } else {
        glFramebufferTexture2D(GL_FRAMEBUFFER, attachment_point, attachment_type, attachment, 0);
    }

    if (point == AttachmentPoint::COLOR) {
        GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
        glDrawBuffers(1, draw_buffers);
    }
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

void gst::GraphicsDeviceImpl::update_texture_storage(
    GLenum target,
    GLenum internal_format,
    GLenum source_format,
    unsigned int width,
    unsigned int height,
    ShadowedData const & data)
{
    GLenum type = 0;

    auto data_type = data.get_type();
    switch (data_type) {
        case DataType::INT_ARRAY:
            type = GL_INT;
            break;
        case DataType::FLOAT_ARRAY:
            type = GL_FLOAT;
            break;
        case DataType::NONE:
        case DataType::UCHAR_ARRAY:
        default:
            type = GL_UNSIGNED_BYTE;
            break;
    }

    glTexImage2D(
        target,
        0,
        internal_format,
        width,
        height,
        0,
        source_format,
        type,
        data.get_data()
    );
}
