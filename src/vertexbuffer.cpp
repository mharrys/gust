#include "vertexbuffer.hpp"

gst::VertexBuffer::VertexBuffer(VertexAttribute attribute)
    : VertexBuffer(VertexAttributes({ attribute }))
{
}

gst::VertexBuffer::VertexBuffer(VertexAttributes attributes)
    : Buffer(BufferTarget::ARRAY),
      attributes(attributes)
{
}
