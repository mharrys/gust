#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "graphicsresource.hpp"
#include "textureparam.hpp"

#include <vector>

namespace gst
{
    class Image;
    class Resolution;

    // The responsibility of this class is to mirror a texture object on the
    // graphics card.
    class Texture : public GraphicsResource {
    public:
        virtual ~Texture() = default;
        // Set storage size.
        virtual void set_size(Resolution size) = 0;
        // Set storage data.
        virtual void set_data(std::vector<unsigned char> const & data) = 0;
        // Set storage parameters.
        virtual void set_param(TextureParam const & param) = 0;
        // Return texture target.
        virtual TextureTarget get_target() const = 0;
        // Return storage size.
        virtual Resolution get_size() const = 0;
        // Return storage data.
        virtual std::vector<unsigned char> get_data() const = 0;
        // Return storage parameters.
        virtual TextureParam get_param() const = 0;
    };
}

#endif
