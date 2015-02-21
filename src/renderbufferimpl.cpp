#include "renderbufferimpl.hpp"

gst::RenderbufferImpl::RenderbufferImpl(
    std::shared_ptr<GraphicsDevice> device,
    Resolution size,
    RenderbufferFormat format)
    : handle(device->create_renderbuffer()),
      device(device),
      size(size),
      format(format),
      dirty(true)
{
}

gst::RenderbufferImpl::~RenderbufferImpl()
{
    device->destroy_renderbuffer(handle);
}

void gst::RenderbufferImpl::set_size(Resolution size)
{
    this->size = size;
    dirty = true;
}

void gst::RenderbufferImpl::set_format(RenderbufferFormat format)
{
    this->format = format;
    dirty = true;
}

gst::Resolution gst::RenderbufferImpl::get_size() const
{
    return size;
}

gst::RenderbufferFormat gst::RenderbufferImpl::get_format() const
{
    return format;
}

void gst::RenderbufferImpl::bind()
{
    device->bind_renderbuffer(handle);
}

void gst::RenderbufferImpl::sync()
{
    if (dirty) {
        dirty = false;
        device->renderbuffer_storage(size, format);
    }
}
