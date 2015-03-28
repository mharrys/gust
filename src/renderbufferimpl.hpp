#ifndef RENDERBUFFERIMPL_HPP_INCLUDED
#define RENDERBUFFERIMPL_HPP_INCLUDED

#include "renderbuffer.hpp"
#include "resolution.hpp"

namespace gst
{
    class RenderbufferImpl : public Renderbuffer {
    public:
        RenderbufferImpl(
            Resolution size,
            RenderbufferFormat format);
        void set_size(Resolution size) final;
        void set_format(RenderbufferFormat format) final;
        Resolution get_size() const final;
        RenderbufferFormat get_format() const final;
    private:
        Resolution size;
        RenderbufferFormat format;
    };
}

#endif
