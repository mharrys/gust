#ifndef TEXTURE2D_HPP_INCLUDED
#define TEXTURE2D_HPP_INCLUDED

#include "resolution.hpp"
#include "texture.hpp"

#include <memory>

namespace gst
{
    class Texture2d : public Texture {
    public:
        Texture2d(
            Resolution size,
            std::vector<unsigned char> const & data,
            TextureParam const & param);
        void set_size(Resolution size);
        void set_data(std::vector<unsigned char> const & data);
        void set_param(TextureParam const & param);
        TextureTarget get_target() const;
        Resolution get_size() const;
        std::vector<unsigned char> get_data() const;
        TextureParam get_param() const;
    private:
        Resolution size;
        std::vector<unsigned char> data;
        TextureParam param;
    };
}

#endif
