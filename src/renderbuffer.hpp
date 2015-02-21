#ifndef RENDERBUFFER_HPP_INCLUDED
#define RENDERBUFFER_HPP_INCLUDED

#include "resolution.hpp"

namespace gst
{
    class RenderState;

    // Supported renderbuffer storage formats.
    enum class RenderbufferFormat {
        DEPTH_COMPONENT16,
        DEPTH_COMPONENT24,
        DEPTH_COMPONENT32,
        DEPTH_COMPONENT32F
    };

    // The responsibility of this class is to mirror a renderbuffer storage
    // on the graphics card.
    class Renderbuffer {
        friend RenderState;
    public:
        // Set new client storage size.
        virtual void set_size(Resolution size) = 0;
        // Set new client storage format.
        virtual void set_format(RenderbufferFormat format) = 0;
        // Return client storage size.
        virtual Resolution get_size() const = 0;
        // Return client storage format.
        virtual RenderbufferFormat get_format() const = 0;
    protected:
        // Activate this renderbuffer on the graphics card.
        virtual void bind() = 0;
        // Sync current state with graphics card.
        virtual void sync() = 0;
    };
}

#endif
