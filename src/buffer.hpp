#ifndef BUFFER_HPP_INCLUDED
#define BUFFER_HPP_INCLUDED

#include "vertexattrib.hpp"

#include <cstdint>
#include <memory>

namespace gst
{
    class BufferImpl;
    class RenderState;

    enum class BufferTarget {
        ARRAY,
        ELEMENT_ARRAY
    };

    enum class DataUsage {
        STATIC,
        DYNAMIC
    };

    class Buffer {
        friend RenderState;
    public:
        Buffer() = default;
        Buffer(
            std::shared_ptr<RenderState> render_state,
            BufferTarget target);

        bool operator==(Buffer const & other);
        bool operator!=(Buffer const & other);
        explicit operator bool() const;

        void buffer_data(int64_t size, void const * data, DataUsage usage);
        void buffer_sub_data(int64_t offset, int64_t size, void const * data);
    protected:
        void define(VertexAttrib const & attrib);
        void push();
        void pop();
    private:
        std::shared_ptr<BufferImpl> impl;
        std::shared_ptr<RenderState> render_state;
    };
}

#endif
