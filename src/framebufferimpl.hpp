#ifndef FRAMEBUFFERIMPL_HPP_INCLUDED
#define FRAMEBUFFERIMPL_HPP_INCLUDED

#include "framebuffer.hpp"
#include "framebufferattachment.hpp"

namespace gst
{
    class Resolution;

    class FramebufferImpl : public Framebuffer {
    public:
        // Construct framebuffer with a texture as color attachment and
        // renderbuffer as depth attachment with specified size.
        static FramebufferImpl create(Resolution size);
        // Construct empty framebuffer.
        FramebufferImpl() = default;
        // Construct framebuffer from color and depth attachment.
        FramebufferImpl(FramebufferAttachment color, FramebufferAttachment depth);
        void set_color(FramebufferAttachment color) final;
        void set_depth(FramebufferAttachment depth) final;
        FramebufferAttachment get_color_attachment() const final;
        FramebufferAttachment get_depth_attachment() const final;
    private:
        FramebufferAttachment color;
        FramebufferAttachment depth;
    };
}

#endif
