#include "renderbufferimpl.hpp"

gst::RenderbufferImpl::RenderbufferImpl(
    Resolution size,
    RenderbufferFormat format)
    : size(size),
      format(format)
{
    needs_update();
}

void gst::RenderbufferImpl::set_size(Resolution size)
{
    this->size = size;
    needs_update();
}

void gst::RenderbufferImpl::set_format(RenderbufferFormat format)
{
    this->format = format;
    needs_update();
}

gst::Resolution gst::RenderbufferImpl::get_size() const
{
    return size;
}

gst::RenderbufferFormat gst::RenderbufferImpl::get_format() const
{
    return format;
}
