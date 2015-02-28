#ifndef FRAMEBUFFER_HPP_INCLUDED
#define FRAMEBUFFER_HPP_INCLUDED

#include "graphicsresource.hpp"

#include <memory>

namespace gst
{
    class Renderbuffer;
    class Texture;

    // The responsibility of this class is to mirror a framebuffer object on
    // the graphics card.
    class Framebuffer : public GraphicsResource {
    public:
        virtual ~Framebuffer() = default;
        // Attach color.
        virtual void attach(std::shared_ptr<Texture> color) = 0;
        // Attach depth.
        virtual void attach(std::shared_ptr<Renderbuffer> depth) = 0;
        // Return attached color.
        virtual std::shared_ptr<Texture> get_color() const = 0;
        // Return attached depth.
        virtual std::shared_ptr<Renderbuffer> get_depth() const = 0;
    };
}

#endif
