#ifndef FRAMEBUFFER_HPP_INCLUDED
#define FRAMEBUFFER_HPP_INCLUDED

#include "graphicsresource.hpp"

namespace gst
{
    class FramebufferAttachment;

    // The responsibility of this class is to mirror a framebuffer object on
    // the graphics card.
    class Framebuffer : public GraphicsResource {
    public:
        virtual ~Framebuffer() = default;
        // Set color attachment for specified buffer.
        virtual void set_color(FramebufferAttachment color) = 0;
        // Set depth attachment.
        virtual void set_depth(FramebufferAttachment depth) = 0;
        // Return color attachment.
        virtual FramebufferAttachment get_color() const = 0;
        // Return depth attachment.
        virtual FramebufferAttachment get_depth() const = 0;
    };
}

#endif
