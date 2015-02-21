#include "rendertarget.hpp"

gst::RenderTarget::RenderTarget(
    Framebuffer & framebuffer,
    Resolution size)
    : framebuffer(framebuffer),
      size(size)
{
}

void gst::RenderTarget::set_size(Resolution size)
{
    if (this->size != size) {
        this->size = size;
        framebuffer.get_color().set_image(size);
        framebuffer.get_depth()->set_size(size);
    }
}

gst::Resolution gst::RenderTarget::get_size() const
{
    return size;
}
