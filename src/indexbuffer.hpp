#ifndef INDEXBUFFER_HPP_INCLUDED
#define INDEXBUFFER_HPP_INCLUDED

#include "buffer.hpp"

#include <vector>

namespace gst
{
    class VertexArray;

    template<typename T>
    class IndexBuffer : public Buffer {
        friend VertexArray;
    public:
        IndexBuffer() = default;
        IndexBuffer(
            std::shared_ptr<RenderState> render_state,
            DataType type);

        void buffer_data(DataUsage usage = DataUsage::STATIC);
        void buffer_sub_data(int first, int count);

        DataType get_type() const;

        std::vector<T> data;
    private:
        void use();

        DataType type;
        std::size_t bytes;
    };
}

template<typename T>
gst::IndexBuffer<T>::IndexBuffer(
    std::shared_ptr<RenderState> render_state,
    DataType type)
    : Buffer(render_state, BufferTarget::ELEMENT_ARRAY),
      type(type),
      bytes(sizeof(T))
{
}

template<typename T>
void gst::IndexBuffer<T>::buffer_data(DataUsage usage)
{
    Buffer::buffer_data(bytes * data.size(), &data[0], usage);
}

template<typename T>
void gst::IndexBuffer<T>::buffer_sub_data(int first, int count)
{
    Buffer::buffer_sub_data(bytes * first, bytes * count, &data[0]);
}

template<typename T>
gst::DataType gst::IndexBuffer<T>::get_type() const
{
    return type;
}

template<typename T>
void gst::IndexBuffer<T>::use()
{
    Buffer::push();
    Buffer::pop();
}


#endif
