#ifndef FRAMEBUFFER_HPP_INCLUDED
#define FRAMEBUFFER_HPP_INCLUDED

#include "renderbuffer.hpp"
#include "texture.hpp"

#include <memory>
#include <string>
#include <vector>

namespace gst
{
    class FramebufferImpl;
    class RenderState;

    class Framebuffer {
        friend RenderState;
    public:
        Framebuffer() = default;
        Framebuffer(
            std::shared_ptr<RenderState> render_state,
            Texture & color,
            Renderbuffer & depth);

        bool operator==(Framebuffer const & other);
        bool operator!=(Framebuffer const & other);
        explicit operator bool() const;

        Texture & get_color();
        Renderbuffer & get_depth();

        std::vector<std::string> check_status();
    private:
        void push();
        void pop();

        std::shared_ptr<FramebufferImpl> impl;
        std::shared_ptr<RenderState> render_state;
        Texture color;
        Renderbuffer depth;
    };
}

#endif
