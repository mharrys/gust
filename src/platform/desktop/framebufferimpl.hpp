#ifndef FRAMEBUFFERIMPL_HPP_INCLUDED
#define FRAMEBUFFERIMPL_HPP_INCLUDED

#include "gl.hpp"
#include "resolution.hpp"

#include <memory>
#include <string>
#include <vector>

namespace gst
{
    class RenderbufferImpl;
    class RenderStateImpl;
    class Texture2d;

    class FramebufferImpl {
        friend RenderStateImpl;
    public:
        FramebufferImpl();
        ~FramebufferImpl();
        void attach(Texture2d const & color);
        void attach(RenderbufferImpl const & depth);
        std::vector<std::string> check_status();
    private:
        void bind();

        GLuint id;
    };
}

#endif
