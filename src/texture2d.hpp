#ifndef TEXTURE2D_HPP_INCLUDED
#define TEXTURE2D_HPP_INCLUDED

#include "resolution.hpp"
#include "texture.hpp"

#include <memory>

namespace gst
{
    class ShadowedData;

    // The responsibility of this class is to mirror a 2-dimensional texture.
    class Texture2D : public Texture {
    public:
        // Construct texture with empty data.
        static Texture2D create_empty(Resolution size);
        // Construct empty texture.
        Texture2D() = default;
        // Construct texture of specified size and data.
        Texture2D(Resolution size, std::unique_ptr<ShadowedData> data);

        // Set storage size.
        void set_size(Resolution size);
        // Set storage data.
        void set_data(std::unique_ptr<ShadowedData> data);
        // Update storage data.
        ShadowedData & update_data();

        TextureTarget get_target() const final;
        // Return storage size.
        Resolution get_size() const;
        // Return storage data.
        ShadowedData const & get_data() const;
    private:
        Resolution size;
        std::unique_ptr<ShadowedData> data;
    };
}

#endif
