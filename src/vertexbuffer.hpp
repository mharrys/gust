#ifndef VERTEXBUFFER_HPP_INCLUDED
#define VERTEXBUFFER_HPP_INCLUDED

#include "bufferimpl.hpp"
#include "vertexattribute.hpp"

#include <vector>

namespace gst
{
    // The responsibility of this class is to mirror a vertex buffer object on
    // the graphics card.
    class VertexBuffer : public BufferImpl {
    public:
        VertexBuffer(VertexAttribute attribute);
        VertexBuffer(std::initializer_list<VertexAttribute> attributes);
        // Return vertex attributes.
        std::vector<VertexAttribute> get_attributes() const;
    private:
        std::vector<VertexAttribute> attributes;
    };
}

#endif
