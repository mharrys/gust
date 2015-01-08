#ifndef RENDERTARGET_HPP_INCLUDED
#define RENDERTARGET_HPP_INCLUDED

#include "framebuffer.hpp"
#include "resolution.hpp"

namespace gst
{
    class Renderer;
    class RenderState;

    class RenderTarget {
        friend Renderer;
        friend RenderState;
    public:
        RenderTarget() = default;
        RenderTarget(
            Framebuffer & framebuffer,
            Resolution size);
        void set_size(Resolution size);
        Resolution get_size() const;
    private:
        Framebuffer framebuffer;
        Resolution size;
    };
}

#endif
