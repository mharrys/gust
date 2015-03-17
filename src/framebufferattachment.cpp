#include "framebufferattachment.hpp"

#include "texturecube.hpp"

gst::FramebufferAttachment::FramebufferAttachment(
    AttachmentType type,
    std::shared_ptr<GraphicsResource> attachment)
    : type(type),
      attachment(attachment)
{
}

gst::FramebufferAttachment::FramebufferAttachment(
    CubeFace face,
    std::shared_ptr<GraphicsResource> attachment)
    : attachment(attachment)
{
    switch (face) {
    case CubeFace::POSITIVE_X:
        type = gst::AttachmentType::TEXTURE_CUBE_POSITIVE_X;
        break;
    case CubeFace::NEGATIVE_X:
        type = gst::AttachmentType::TEXTURE_CUBE_NEGATIVE_X;
        break;
    case CubeFace::POSITIVE_Y:
        type = gst::AttachmentType::TEXTURE_CUBE_POSITIVE_Y;
        break;
    case CubeFace::NEGATIVE_Y:
        type = gst::AttachmentType::TEXTURE_CUBE_NEGATIVE_Y;
        break;
    case CubeFace::POSITIVE_Z:
        type = gst::AttachmentType::TEXTURE_CUBE_POSITIVE_Z;
        break;
    case CubeFace::NEGATIVE_Z:
        type = gst::AttachmentType::TEXTURE_CUBE_NEGATIVE_Z;
        break;
    }
}

gst::AttachmentType gst::FramebufferAttachment::get_type() const
{
    return type;
}

std::shared_ptr<gst::GraphicsResource> gst::FramebufferAttachment::get_attachment() const
{
    return attachment;
}
