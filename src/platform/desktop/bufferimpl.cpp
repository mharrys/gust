#include "bufferimpl.hpp"

gst::BufferImpl::BufferImpl(BufferTarget target)
{
    glGenBuffers(1, &id);
    this->target = translator.translate(target);
}

gst::BufferImpl::~BufferImpl()
{
    glDeleteBuffers(1, &id);
}

void gst::BufferImpl::buffer_data(int64_t size, void const * data, DataUsage usage)
{
    glBufferData(target, size, data, translator.translate(usage));
}

void gst::BufferImpl::buffer_sub_data(int64_t offset, int64_t size, void const * data)
{
    glBufferSubData(target, offset, size, data);
}

void gst::BufferImpl::bind()
{
    glBindBuffer(target, id);
}
