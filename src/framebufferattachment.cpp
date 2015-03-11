#include "framebufferattachment.hpp"

gst::FramebufferAttachment::FramebufferAttachment(
    AttachmentType type,
    std::shared_ptr<GraphicsResource> attachment)
    : type(type),
      attachment(attachment)
{
}

gst::AttachmentType gst::FramebufferAttachment::get_type() const
{
    return type;
}

std::shared_ptr<gst::GraphicsResource> gst::FramebufferAttachment::get_attachment() const
{
    return attachment;
}
