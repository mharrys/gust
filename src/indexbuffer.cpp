#include "indexbuffer.hpp"

#include "shadoweddataimpl.hpp"

gst::IndexBuffer::IndexBuffer()
    : BufferImpl(BufferTarget::ELEMENT_ARRAY, std::make_shared<ShadowedDataImpl>())
{
}
