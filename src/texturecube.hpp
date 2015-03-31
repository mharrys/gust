#ifndef TEXTURECUBE_HPP_INCLUDED
#define TEXTURECUBE_HPP_INCLUDED

#include "resolution.hpp"
#include "texture.hpp"

#include <array>
#include <memory>

namespace gst
{
    class ShadowedData;

    // Specifies each face on a texture cube.
    enum class CubeFace {
        POSITIVE_X,
        NEGATIVE_X,
        POSITIVE_Y,
        NEGATIVE_Y,
        POSITIVE_Z,
        NEGATIVE_Z
    };

    // Enum iterator.
    const std::array<CubeFace, 6> CUBE_FACES = {
        CubeFace::POSITIVE_X,
        CubeFace::NEGATIVE_X,
        CubeFace::POSITIVE_Y,
        CubeFace::NEGATIVE_Y,
        CubeFace::POSITIVE_Z,
        CubeFace::NEGATIVE_Z
    };

    typedef std::array<std::unique_ptr<ShadowedData>, 6> CubeData;

    // The responsibility of this class is to mirror a texture cube map
    // consisting of six 2-dimensional textures on the graphics card.
    class TextureCube : public Texture {
    public:
        // Construct texture cube with empty data.
        static TextureCube create_empty(unsigned int size);
        // Construct empty texture cube.
        TextureCube() = default;
        // Construct texture cube of specified size and data.
        TextureCube(unsigned int size, CubeData cube_data);

        // Set storage size for one face, every face must have equal width and
        // height.
        void set_size(unsigned int size);
        // Set storage data for specified face.
        void set_data(CubeFace face, std::unique_ptr<ShadowedData> data);
        // Update storage data for specified face.
        ShadowedData & update_data(CubeFace face);

        TextureTarget get_target() const final;
        // Return storage size for one face.
        Resolution get_size() const;
        // Return storage data for specified face.
        ShadowedData const & get_data(CubeFace face) const;
    private:
        Resolution size;
        CubeData cube_data;
    };
}

#endif
