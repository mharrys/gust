#ifndef RENDERBUFFER_HPP_INCLUDED
#define RENDERBUFFER_HPP_INCLUDED

#include "resolution.hpp"

#include <memory>

namespace gst
{
    class Framebuffer;
    class RenderbufferImpl;
    class RenderState;

    enum class RenderbufferFormat {
        DEPTH_COMPONENT16,
        DEPTH_COMPONENT24,
        DEPTH_COMPONENT32,
        DEPTH_COMPONENT32F
    };

    class Renderbuffer {
        friend Framebuffer;
        friend RenderState;
    public:
        Renderbuffer() = default;
        Renderbuffer(
            Resolution size,
            RenderbufferFormat format);

        bool operator==(Renderbuffer const & other);
        bool operator!=(Renderbuffer const & other);
        explicit operator bool() const;

        void set_storage(Resolution size);
        void set_storage(RenderbufferFormat format);
        void set_storage(Resolution size, RenderbufferFormat format);

        Resolution get_size() const;
        RenderbufferFormat get_format() const;
    private:
        void refresh();

        std::shared_ptr<RenderbufferImpl> impl;
        Resolution size;
        RenderbufferFormat format;
        bool dirty;
    };
}

#endif
