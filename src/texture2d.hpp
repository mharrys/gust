#ifndef TEXTURE2D_HPP_INCLUDED
#define TEXTURE2D_HPP_INCLUDED

#include "resolution.hpp"
#include "texture.hpp"

namespace gst
{
    // The responsibility of this class is to mirror a 2-dimensional texture.
    class Texture2D : public Texture {
    public:
        Texture2D(Resolution size);
        Texture2D(
            Resolution size,
            TextureData const & data);
        // Set storage size.
        void set_size(Resolution size);
        // Set storage data.
        void set_data(TextureData const & data);

        TextureTarget get_target() const final;
        // Return storage size.
        Resolution get_size() const;
        // Return storage data.
        TextureData get_data() const;
    private:
        Resolution size;
        TextureData data;
    };
}

#endif
