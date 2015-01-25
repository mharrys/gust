#ifndef VERTEXBUFFER_HPP_INCLUDED
#define VERTEXBUFFER_HPP_INCLUDED

#include "buffer.hpp"

namespace gst
{
    class VertexArray;

    typedef std::vector<VertexAttribute> VertexAttributes;

    class VertexBuffer : public Buffer {
        friend VertexArray;
    public:
        VertexBuffer(VertexAttribute attribute);
        VertexBuffer(VertexAttributes attributes);
    private:
        VertexAttributes attributes;
    };
}

#endif
