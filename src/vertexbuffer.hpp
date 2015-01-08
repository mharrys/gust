#ifndef VERTEXBUFFER_HPP_INCLUDED
#define VERTEXBUFFER_HPP_INCLUDED

#include "buffer.hpp"

#include <vector>

namespace gst
{
    class VertexArray;

    template<typename T>
    class VertexBuffer : public Buffer {
        friend VertexArray;
    public:
        VertexBuffer() = default;
        VertexBuffer(
            std::shared_ptr<RenderState> render_state,
            VertexAttrib attrib);
        VertexBuffer(
            std::shared_ptr<RenderState> render_state,
            std::vector<VertexAttrib> attribs);

        void buffer_data(DataUsage usage = DataUsage::STATIC);
        void buffer_sub_data(int first, int count);

        std::vector<T> data;
    private:
        void use();

        std::vector<VertexAttrib> attribs;
        std::size_t bytes;
    };
}

template<typename T>
gst::VertexBuffer<T>::VertexBuffer(
    std::shared_ptr<RenderState> render_state,
    VertexAttrib attrib)
    : VertexBuffer(render_state, std::vector<VertexAttrib>{ attrib })
{
}

template<typename T>
gst::VertexBuffer<T>::VertexBuffer(
    std::shared_ptr<RenderState> render_state,
    std::vector<VertexAttrib> attribs)
    : Buffer(render_state, BufferTarget::ARRAY),
      attribs(attribs),
      bytes(sizeof(T))
{
}

template<typename T>
void gst::VertexBuffer<T>::buffer_data(DataUsage usage)
{
    Buffer::buffer_data(bytes * data.size(), &data[0], usage);
}

template<typename T>
void gst::VertexBuffer<T>::buffer_sub_data(int first, int count)
{
    Buffer::buffer_sub_data(bytes * first, bytes * count, &data[0]);
}

template<typename T>
void gst::VertexBuffer<T>::use()
{
    Buffer::push();
    for (auto attrib : attribs) {
        Buffer::define(attrib);
    }
    Buffer::pop();
}

#endif
