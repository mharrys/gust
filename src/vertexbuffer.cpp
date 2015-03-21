#include "vertexbuffer.hpp"

#include "shadoweddataimpl.hpp"

gst::VertexBuffer::VertexBuffer(VertexAttribute attribute)
    : VertexBuffer(std::initializer_list<VertexAttribute>{ attribute })
{
}

gst::VertexBuffer::VertexBuffer(std::initializer_list<VertexAttribute> attributes)
    : BufferImpl(BufferTarget::ARRAY, std::make_shared<ShadowedDataImpl>()),
      attributes(attributes)
{
}

std::vector<gst::VertexAttribute> gst::VertexBuffer::get_attributes() const
{
    return attributes;
}
