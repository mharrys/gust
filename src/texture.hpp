#ifndef TEXTURE_HPP_INCLUDED
#define TEXTURE_HPP_INCLUDED

#include "image.hpp"
#include "resolution.hpp"
#include "textureparam.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Framebuffer;
    class RenderState;

    class Texture {
        friend RenderState;
    public:
        virtual void set_size(Resolution size) = 0;
        virtual void set_data(std::vector<unsigned char> const & data) = 0;
        virtual void set_image(Image const & image) = 0;
        virtual void set_param(TextureParam const & param) = 0;
    protected:
        virtual void bind(int unit) = 0;
        virtual void sync() = 0;
    };
}

#endif
