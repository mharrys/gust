#ifndef VERTEXATTRIBUTE_HPP_INCLUDED
#define VERTEXATTRIBUTE_HPP_INCLUDED

#include <memory>

namespace gst
{
    // default vertex attributes
    enum AttributeIndex {
        POSITION = 0,
        NORMAL,
        COLOR,
        TEX_COORD,
        INDICES
    };

    enum class VertexDataType {
        INT,
        UNSIGNED_INT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4
    };

    class VertexAttribute {
    public:
        VertexAttribute(
            int index,
            int components,
            VertexDataType type);
        VertexAttribute(
            int index,
            int components,
            VertexDataType type,
            bool normalized,
            size_t stride_bytes,
            size_t offset_bytes);
        int get_index() const;
        int get_components() const;
        VertexDataType get_type() const;
        bool get_normalized() const;
        size_t get_stride_bytes() const;
        size_t get_offset_bytes() const;
    private:
        int index;
        int components;
        VertexDataType type;
        bool normalized;
        size_t stride_bytes;
        size_t offset_bytes;
    };
}

#endif
