#ifndef FRAMEBUFFERATTACHMENT_HPP_INCLUDED
#define FRAMEBUFFERATTACHMENT_HPP_INCLUDED

#include <memory>

namespace gst
{
    class GraphicsResource;
    class Renderbuffer;
    class Texture2D;
    class TextureCube;

    enum class CubeFace;

    // Specifices framebuffer attachment types.
    enum class AttachmentType {
        RENDERBUFFER,            // Renderbuffer, sampling will not be possible.
        TEXTURE_2D,              // 2-dimensional texture.
        TEXTURE_CUBE_POSITIVE_X, // +X face in a cube map texture.
        TEXTURE_CUBE_NEGATIVE_X, // -X face in a cube map texture.
        TEXTURE_CUBE_POSITIVE_Y, // +Y face in a cube map texture.
        TEXTURE_CUBE_NEGATIVE_Y, // -Y face in a cube map texture.
        TEXTURE_CUBE_POSITIVE_Z, // +Z face in a cube map texture.
        TEXTURE_CUBE_NEGATIVE_Z  // -Z face in a cube map texture.
    };

    // Specifices framebuffer attachment point.
    enum class AttachmentPoint {
        DEPTH, // Depth attachment.
        COLOR  // Color attachment. Always first color buffer.
    };

    // The responsibility of this class is to describe a framebuffer
    // attachment.
    class FramebufferAttachment {
    public:
        FramebufferAttachment() = default;
        FramebufferAttachment(
            std::shared_ptr<Renderbuffer> attachment);
        FramebufferAttachment(
            std::shared_ptr<Texture2D> attachment);
        FramebufferAttachment(
            std::shared_ptr<TextureCube> attachment,
            CubeFace face);
        // Return type of attachment.
        AttachmentType get_type() const;
        // Return attachment.
        std::shared_ptr<GraphicsResource> get_attachment() const;
    private:
        AttachmentType type;
        std::shared_ptr<GraphicsResource> attachment;
    };
}

#endif
