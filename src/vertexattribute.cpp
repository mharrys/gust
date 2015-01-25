#include "vertexattribute.hpp"

gst::VertexAttribute::VertexAttribute(
    int index,
    int components,
    DataType type)
    : VertexAttribute(index, components, type, false, 0, 0)
{
}

gst::VertexAttribute::VertexAttribute(
    int index,
    int components,
    DataType type,
    bool normalized,
    size_t stride_bytes,
    size_t offset_bytes)
    : index(index),
      components(components),
      type(type),
      normalized(normalized),
      stride_bytes(stride_bytes),
      offset_bytes(offset_bytes)
{
}

int gst::VertexAttribute::get_index() const
{
    return index;
}

int gst::VertexAttribute::get_components() const
{
    return components;
}

gst::DataType gst::VertexAttribute::get_type() const
{
    return type;
}

bool gst::VertexAttribute::get_normalized() const
{
    return normalized;
}

size_t gst::VertexAttribute::get_stride_bytes() const
{
    return stride_bytes;
}

size_t gst::VertexAttribute::get_offset_bytes() const
{
    return offset_bytes;
}
