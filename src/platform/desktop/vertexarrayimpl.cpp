#include "vertexarrayimpl.hpp"

gst::VertexArrayImpl::VertexArrayImpl()
{
    glGenVertexArrays(1, &id);
}

gst::VertexArrayImpl::~VertexArrayImpl()
{
    glDeleteVertexArrays(1, &id);
}

void gst::VertexArrayImpl::draw_arrays(DrawMode mode, int first, int count) const
{
    glDrawArrays(translator.translate(mode), first, count);
}

void gst::VertexArrayImpl::draw_elements(DrawMode mode, int count, DataType type) const
{
    glDrawElements(translator.translate(mode), count, translator.translate(type), 0);
}

void gst::VertexArrayImpl::define(VertexAttribute const & attrib)
{
    glEnableVertexAttribArray(attrib.get_index());
    glVertexAttribPointer(
        attrib.get_index(),
        attrib.get_components(),
        translator.translate(attrib.get_type()),
        attrib.get_normalized() ? GL_TRUE : GL_FALSE,
        attrib.get_stride_bytes(),
        (GLvoid const *)(attrib.get_offset_bytes())
    );
}

void gst::VertexArrayImpl::bind()
{
    glBindVertexArray(id);
}
