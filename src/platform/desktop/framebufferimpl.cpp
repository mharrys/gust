#include "framebufferimpl.hpp"

#include "renderbufferimpl.hpp"
#include "textureimpl.hpp"

gst::FramebufferImpl::FramebufferImpl()
{
    glGenFramebuffers(1, &id);
}

gst::FramebufferImpl::~FramebufferImpl()
{
    glDeleteFramebuffers(1, &id);
}

void gst::FramebufferImpl::attach(TextureImpl const & color)
{
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color.id, 0);

    GLenum draw_buffers[] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(1, draw_buffers);
}

void gst::FramebufferImpl::attach(RenderbufferImpl const & depth)
{
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depth.id);
}

void gst::FramebufferImpl::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, id);
}

std::vector<std::string> gst::FramebufferImpl::check_status()
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
