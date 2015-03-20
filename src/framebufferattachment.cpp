#include "framebufferattachment.hpp"

#include "renderbuffer.hpp"
#include "texture2d.hpp"
#include "texturecube.hpp"

gst::FramebufferAttachment::FramebufferAttachment(
    std::shared_ptr<Renderbuffer> attachment)
    : type(AttachmentType::RENDERBUFFER),
      attachment(attachment)
{
}

gst::FramebufferAttachment::FramebufferAttachment(
    std::shared_ptr<Texture2D> attachment)
    : type(AttachmentType::TEXTURE_2D),
      attachment(attachment)
{
}

gst::FramebufferAttachment::FramebufferAttachment(
    std::shared_ptr<TextureCube> attachment,
    CubeFace face)
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
