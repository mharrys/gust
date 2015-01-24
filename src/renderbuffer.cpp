#include "renderbuffer.hpp"

#include "renderbufferimpl.hpp"

gst::Renderbuffer::Renderbuffer(
    Resolution size,
    RenderbufferFormat format)
    : impl(std::make_shared<RenderbufferImpl>()),
      size(size),
      format(format),
      dirty(true)
{
}

bool gst::Renderbuffer::operator==(Renderbuffer const & other)
{
    return impl == other.impl;
}

bool gst::Renderbuffer::operator!=(Renderbuffer const & other)
{
    return !(*this == other);
}

gst::Renderbuffer::operator bool() const
{
    return impl != nullptr;
}

void gst::Renderbuffer::set_storage(Resolution size)
{
    set_storage(size, format);
}

void gst::Renderbuffer::set_storage(RenderbufferFormat format)
{
    set_storage(size, format);
}

void gst::Renderbuffer::set_storage(Resolution size, RenderbufferFormat format)
{
    this->size = size;
    this->format = format;
    dirty = true;
}

gst::Resolution gst::Renderbuffer::get_size() const
{
    return size;
}

gst::RenderbufferFormat gst::Renderbuffer::get_format() const
{
    return format;
}

void gst::Renderbuffer::refresh()
{
    if (dirty) {
        dirty = false;
        impl->storage(size, format);
    }
}
