#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "graphicsdevice.hpp"

#include <vector>

namespace gst
{
    class Image;
    class RenderState;
    class Resolution;

    // The responsibility of this class is to mirror a texture object on the
    // graphics card.
    class Texture {
        friend RenderState;
    public:
        virtual ~Texture() = default;
        // Set storage size.
        virtual void set_size(Resolution size) = 0;
        // Set storage data.
        virtual void set_data(std::vector<unsigned char> const & data) = 0;
        // Set storage size and data.
        virtual void set_image(Image const & image) = 0;
        // Set storage parameters.
        virtual void set_param(TextureParam const & param) = 0;
        // Return identifier on the graphics card.
        virtual TextureHandle get_handle() const = 0;
    protected:
        // Notify graphics card to bind this texture.
        virtual void bind(int unit) = 0;
        // Sync client state with graphics card.
        virtual void sync() = 0;
    };
}

#endif
