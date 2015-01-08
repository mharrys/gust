#ifndef RENDERBUFFER_IMPL_HPP_INCLUDED
#define RENDERBUFFER_IMPL_HPP_INCLUDED

#include "resolution.hpp"
#include "translator.hpp"

#include <memory>

namespace gst
{
    class FramebufferImpl;
    class RenderStateImpl;

    class RenderbufferImpl {
        friend FramebufferImpl;
        friend RenderStateImpl;
    public:
        RenderbufferImpl();
        ~RenderbufferImpl();
        void storage(Resolution size);
        void storage(RenderbufferFormat format);
        void storage(Resolution size, RenderbufferFormat format);
    private:
        void bind();
        void storage();

        GLuint id;
        GLenum format;
        Resolution size;

        Translator translator;
    };
}

#endif
