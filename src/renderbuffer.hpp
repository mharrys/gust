#ifndef RENDERBUFFER_HPP_INCLUDED
#define RENDERBUFFER_HPP_INCLUDED

#include "graphicsresource.hpp"
#include "renderbufferformat.hpp"

namespace gst
{
    class Resolution;

    // The responsibility of this class is to mirror a renderbuffer storage
    // on the graphics card.
    class Renderbuffer : public GraphicsResource {
    public:
        virtual ~Renderbuffer() = default;
        // Set new client storage size.
        virtual void set_size(Resolution size) = 0;
        // Set new client storage format.
        virtual void set_format(RenderbufferFormat format) = 0;
        // Return client storage size.
        virtual Resolution get_size() const = 0;
        // Return client storage format.
        virtual RenderbufferFormat get_format() const = 0;
    };
}

#endif
