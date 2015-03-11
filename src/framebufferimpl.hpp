#ifndef FRAMEBUFFERIMPL_HPP_INCLUDED
#define FRAMEBUFFERIMPL_HPP_INCLUDED

#include "framebuffer.hpp"
#include "framebufferattachment.hpp"

namespace gst
{
    class FramebufferImpl : public Framebuffer {
    public:
        FramebufferImpl() = default;
        FramebufferImpl(FramebufferAttachment color, FramebufferAttachment depth);
        void set_color(FramebufferAttachment color) final;
        void set_depth(FramebufferAttachment depth) final;
        FramebufferAttachment get_color() const final;
        FramebufferAttachment get_depth() const final;
    private:
        FramebufferAttachment color;
        FramebufferAttachment depth;
    };
}

#endif
