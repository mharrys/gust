#ifndef VERTEXATTRIBUTE_HPP_INCLUDED
#define VERTEXATTRIBUTE_HPP_INCLUDED

#include <memory>

namespace gst
{
    // Specifies default vertex attributes.
    enum AttributeIndex {
        POSITION = 0,
        NORMAL,
        COLOR,
        TEX_COORD,
        INDICES
    };

    // Specifies vertex data type.
    enum class VertexDataType {
        INT,
        UNSIGNED_INT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4
    };

    // The responsibility of this class is to specify how a vertex stream is
    // stored.
    class VertexAttribute {
    public:
        int index;
        int components;
        VertexDataType type;
        size_t stride_bytes;
        size_t offset_bytes;
    };
}

#endif
