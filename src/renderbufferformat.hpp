#ifndef RENDERBUFFERFORMAT_HPP_INCLUDED
#define RENDERBUFFERFORMAT_HPP_INCLUDED

namespace gst
{
    // Supported renderbuffer storage formats.
    enum class RenderbufferFormat {
        DEPTH_COMPONENT16,
        DEPTH_COMPONENT24,
        DEPTH_COMPONENT32,
        DEPTH_COMPONENT32F
    };
}

#endif
