#ifndef TEXTURE2D_HPP_INCLUDED
#define TEXTURE2D_HPP_INCLUDED

#include "resolution.hpp"
#include "texture.hpp"

#include <vector>

namespace gst
{
    // The responsibility of this class is to mirror a 2-dimensional texture.
    class Texture2d : public Texture {
    public:
        Texture2d(
            Resolution size,
            std::vector<unsigned char> const & data);
        // Set storage size.
        void set_size(Resolution size);
        // Set storage data.
        void set_data(std::vector<unsigned char> const & data);

        TextureTarget get_target() const override;
        // Return storage size.
        Resolution get_size() const;
        // Return storage data.
        std::vector<unsigned char> get_data() const;
    private:
        Resolution size;
        std::vector<unsigned char> data;
    };
}

#endif
