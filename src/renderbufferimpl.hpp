#ifndef RENDERBUFFER_IMPL_HPP_INCLUDED
#define RENDERBUFFER_IMPL_HPP_INCLUDED

#include "renderbuffer.hpp"
#include "resolution.hpp"

#include <memory>

namespace gst
{
    class RenderbufferImpl : public Renderbuffer {
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
        RenderbufferHandle get_handle() const;

        RenderbufferHandle handle;
        std::shared_ptr<GraphicsDevice> device;

        Resolution size;
        RenderbufferFormat format;
        bool dirty;
    };
}

#endif
