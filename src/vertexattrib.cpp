#include "vertexattrib.hpp"

gst::VertexAttrib::VertexAttrib(
    int index,
    int components,
    DataType type)
    : VertexAttrib(index, components, type, false, 0, 0)
{
}

gst::VertexAttrib::VertexAttrib(
    int index,
    int components,
    DataType type,
    bool normalized,
    std::size_t stride_bytes,
    std::size_t offset_bytes)
    : index(index),
      components(components),
      type(type),
      normalized(normalized),
      stride_bytes(stride_bytes),
      offset_bytes(offset_bytes)
{
}
