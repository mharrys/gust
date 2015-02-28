#ifndef FRAMEBUFFERIMPL_HPP_INCLUDED
#define FRAMEBUFFERIMPL_HPP_INCLUDED

#include "framebuffer.hpp"

namespace gst
{
    class FramebufferImpl : public Framebuffer {
    public:
        FramebufferImpl() = default;
        FramebufferImpl(
            std::shared_ptr<Texture> color,
            std::shared_ptr<Renderbuffer> depth);
        void attach(std::shared_ptr<Texture> color);
        void attach(std::shared_ptr<Renderbuffer> depth);
        std::shared_ptr<Texture> get_color() const;
        std::shared_ptr<Renderbuffer> get_depth() const;
    private:
        std::shared_ptr<Texture> color;
        std::shared_ptr<Renderbuffer> depth;
    };
}

#endif
