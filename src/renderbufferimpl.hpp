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
        void set_size(Resolution size);
        void set_format(RenderbufferFormat format);
        Resolution get_size() const;
        RenderbufferFormat get_format() const;
    private:
        Resolution size;
        RenderbufferFormat format;
    };
}

#endif
