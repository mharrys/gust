#ifndef TEXTURECUBE_HPP_INCLUDED
#define TEXTURECUBE_HPP_INCLUDED

#include "resolution.hpp"
#include "texture.hpp"

#include <array>
#include <vector>

namespace gst
{
    // Specifies each face on a texture cube.
    enum class CubeFace {
        POSITIVE_X,
        NEGATIVE_X,
        POSITIVE_Y,
        NEGATIVE_Y,
        POSITIVE_Z,
        NEGATIVE_Z
    };

    typedef std::array<std::vector<unsigned char>, 6> CubeData;

    // The responsibility of this class is to mirror a texture cube map
    // consisting of six 2-dimensional textures on the graphics card.
    class TextureCube : public Texture {
    public:
        TextureCube(
            unsigned int size,
            CubeData cube_data);
        // Set storage size for one face, every face must have equal width and
        // height.
        void set_size(unsigned int size);
        // Set storage for specified face.
        void set_data(CubeFace face, std::vector<unsigned char> const & data);

        TextureTarget get_target() const override;
        // Return storage size for one face.
        Resolution get_size() const;
        // Return storage data for specified face.
        std::vector<unsigned char> get_data(CubeFace face) const;
    private:
        Resolution size;
        CubeData cube_data;
    };
}

#endif
