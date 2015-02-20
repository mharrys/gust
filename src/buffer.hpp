#ifndef BUFFER_HPP_INCLUDED
#define BUFFER_HPP_INCLUDED

namespace gst
{
    class RenderState;

    enum class BufferTarget {
        ARRAY,
        ELEMENT_ARRAY
    };

    enum class DataUsage {
        STATIC,
        DYNAMIC
    };

    // The responsibility of this class is to mirror a buffer object on the
    // graphics card.
    class Buffer {
        friend RenderState;
    public:
        // Return buffer target.
        virtual BufferTarget get_target() const = 0;
        // Return buffer data usage.
        virtual DataUsage get_usage() const = 0;
        // Return buffer data size in bytes.
        virtual unsigned int get_size_bytes() const = 0;
        // Return the number of elements in the buffer data.
        virtual unsigned int get_count() const = 0;
    protected:
        // Notify graphics card to bind this buffer.
        virtual void bind() = 0;
        // Sync client state with graphics card.
        virtual void sync() = 0;
    };
}

#endif
