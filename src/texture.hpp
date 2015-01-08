#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "textureparam.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Image;
    class Framebuffer;
    class RenderState;
    class Resolution;
    class TextureImpl;

    // TODO: Texture2D, TextureCube
    class Texture {
        friend Framebuffer;
        friend RenderState;
    public:
        Texture() = default;
        Texture(
            std::shared_ptr<RenderState> render_state,
            Resolution size,
            std::vector<unsigned char> const & data = {},
            TextureParam const & param = {});
        Texture(
            std::shared_ptr<RenderState> render_state,
            Image const & image,
            TextureParam const & param = {});

        bool operator==(Texture const & other);
        bool operator!=(Texture const & other);
        explicit operator bool() const;

        void update(Resolution size, std::vector<unsigned char> const & data = {});
        void update(TextureParam const & param = {});
    private:
        void push();
        void pop();

        std::shared_ptr<TextureImpl> impl;
        std::shared_ptr<RenderState> render_state;
    };
}

#endif
