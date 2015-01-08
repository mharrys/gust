#ifndef VERTEXATTRIB_HPP_INCLUDED
#define VERTEXATTRIB_HPP_INCLUDED

#include <cstdint>

namespace gst
{
    // default vertex attrib indices
    enum AttribIndex {
        POSITION = 0,
        NORMAL,
        COLOR,
        TEX_COORD,
        INDICES
    };

    enum class DataType {
        INT,
        UNSIGNED_INT,
        FLOAT
    };

    struct VertexAttrib {
        VertexAttrib(
            int index,
            int components,
            DataType type);
        VertexAttrib(
            int index,
            int components,
            DataType type,
            bool normalized,
            std::size_t stride_bytes,
            std::size_t offset_bytes);

        int index;
        int components;
        DataType type;
        bool normalized;
        std::size_t stride_bytes;
        std::size_t offset_bytes;
    };
}

#endif
