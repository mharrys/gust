#ifndef INDEXBUFFER_HPP_INCLUDED
#define INDEXBUFFER_HPP_INCLUDED

#include "bufferimpl.hpp"

namespace gst
{
    // The responsibility of this class is to mirror a index buffer object on
    // the graphics card.
    class IndexBuffer : public BufferImpl {
    public:
        IndexBuffer();
    };
}

#endif
