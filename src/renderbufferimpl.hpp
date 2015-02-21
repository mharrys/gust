#ifndef RENDERBUFFER_IMPL_HPP_INCLUDED
#define RENDERBUFFER_IMPL_HPP_INCLUDED

#include "graphicsdevice.hpp"
#include "renderbuffer.hpp"

#include <memory>

namespace gst
{
    class FramebufferImpl;

    class RenderbufferImpl : public Renderbuffer {
        friend FramebufferImpl;
    public:
        RenderbufferImpl(
            std::shared_ptr<GraphicsDevice> device,
            Resolution size,
            RenderbufferFormat format);
        ~RenderbufferImpl();
        void set_size(Resolution size);
        void set_format(RenderbufferFormat format);
        Resolution get_size() const;
        RenderbufferFormat get_format() const;
    private:
        void bind();
        void sync();

        RenderbufferHandle handle;
        std::shared_ptr<GraphicsDevice> device;

        Resolution size;
        RenderbufferFormat format;
        bool dirty;
    };
}

#endif
