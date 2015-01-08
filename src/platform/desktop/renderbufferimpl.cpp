#include "renderbufferimpl.hpp"

gst::RenderbufferImpl::RenderbufferImpl()
{
    glGenRenderbuffers(1, &id);
}

gst::RenderbufferImpl::~RenderbufferImpl()
{
    glDeleteRenderbuffers(1, &id);
}

void gst::RenderbufferImpl::storage(Resolution size)
{
    this->size = size;
    storage();
}

void gst::RenderbufferImpl::storage(RenderbufferFormat format)
{
    this->format = translator.translate(format);
    storage();
}

void gst::RenderbufferImpl::storage(Resolution size, RenderbufferFormat format)
{
    this->size = size;
    this->format = translator.translate(format);
    storage();
}

void gst::RenderbufferImpl::bind()
{
    glBindRenderbuffer(GL_RENDERBUFFER, id);
}

void gst::RenderbufferImpl::storage()
{
    glRenderbufferStorage(GL_RENDERBUFFER, format, size.get_width(), size.get_height());
}
