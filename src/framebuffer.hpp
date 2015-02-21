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
            Texture & color,
            std::shared_ptr<Renderbuffer> depth);

        bool operator==(Framebuffer const & other);
        bool operator!=(Framebuffer const & other);
        explicit operator bool() const;

        void attach(Texture & color);
        void attach(std::shared_ptr<Renderbuffer> depth);

        Texture get_color() const;
        std::shared_ptr<Renderbuffer> get_depth() const;
        std::vector<std::string> get_status() const;
    private:
        void refresh(RenderState & render_state);

        std::shared_ptr<FramebufferImpl> impl;
        Texture color;
        std::shared_ptr<Renderbuffer> depth;
        bool color_dirty;
        bool depth_dirty;
        std::vector<std::string> status;
    };
}

#endif
