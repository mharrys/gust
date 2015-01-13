#include "renderstateimpl.hpp"

#include "bufferimpl.hpp"
#include "color.hpp"
#include "framebufferimpl.hpp"
#include "renderbufferimpl.hpp"
#include "programimpl.hpp"
#include "textureimpl.hpp"
#include "vertexarrayimpl.hpp"
#include "viewport.hpp"

void gst::RenderStateImpl::clear_buffers(bool color, bool depth)
{
    int mask = 0;
    mask |= color ? GL_COLOR_BUFFER_BIT : 0;
    mask |= depth ? GL_DEPTH_BUFFER_BIT : 0;
    glClear(mask);
}

void gst::RenderStateImpl::set_clear_color(Color const & clear_color)
{
    glClearColor(
        clear_color.get_red(),
        clear_color.get_green(),
        clear_color.get_blue(),
        clear_color.get_alpha()
    );
}

void gst::RenderStateImpl::set_blend_mode(BlendMode blend_mode)
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

void gst::RenderStateImpl::set_cull_face(CullFace cull_face)
{
    if (cull_face == CullFace::NONE) {
        glDisable(GL_CULL_FACE);
    } else {
        glEnable(GL_CULL_FACE);
        glCullFace(translator.translate(cull_face));
    }
}

void gst::RenderStateImpl::set_depth_mask(bool depth_mask)
{
    glDepthMask(depth_mask ? GL_TRUE : GL_FALSE);
}

void gst::RenderStateImpl::set_depth_test(bool depth_test)
{
    if (depth_test) {
        glEnable(GL_DEPTH_TEST);
    } else {
        glDisable(GL_DEPTH_TEST);
    }
}

void gst::RenderStateImpl::set_buffer(BufferImpl & buffer)
{
    buffer.bind();
}

void gst::RenderStateImpl::set_framebuffer(FramebufferImpl & framebuffer)
{
    framebuffer.bind();
}

void gst::RenderStateImpl::set_framebuffer_none()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void gst::RenderStateImpl::set_renderbuffer(RenderbufferImpl & renderbuffer)
{
    renderbuffer.bind();
}

void gst::RenderStateImpl::set_renderbuffer_none()
{
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void gst::RenderStateImpl::set_program(ProgramImpl & program)
{
    program.use();
}

void gst::RenderStateImpl::set_program_none()
{
    glUseProgram(0);
}

void gst::RenderStateImpl::set_texture(TextureImpl & texture, int unit)
{
    texture.bind(unit);
}

void gst::RenderStateImpl::set_texture_none(int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void gst::RenderStateImpl::set_vertex_array(VertexArrayImpl & vertex_array)
{
    vertex_array.bind();
}

void gst::RenderStateImpl::set_vertex_array_none()
{
    glBindVertexArray(0);
}

void gst::RenderStateImpl::set_viewport(Viewport const & viewport)
{
    glViewport(
        viewport.get_x(),
        viewport.get_y(),
        viewport.get_width(),
        viewport.get_height()
    );
}

std::vector<std::string> gst::RenderStateImpl::check_errors() const
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
