#ifndef RENDERBUFFER_HPP_INCLUDED
#define RENDERBUFFER_HPP_INCLUDED

#include <memory>

namespace gst
{
    class Framebuffer;
    class RenderbufferImpl;
    class Resolution;
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
            std::shared_ptr<RenderState> render_state,
            Resolution size,
            RenderbufferFormat format);

        bool operator==(Renderbuffer const & other);
        bool operator!=(Renderbuffer const & other);
        explicit operator bool() const;

        void update(Resolution size);
        void update(RenderbufferFormat format);
        void update(Resolution size, RenderbufferFormat format);
    private:
        void push();
        void pop();

        std::shared_ptr<RenderbufferImpl> impl;
        std::shared_ptr<RenderState> render_state;
    };
}

#endif
