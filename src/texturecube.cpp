#include "texturecube.hpp"

gst::TextureCube::TextureCube(
    unsigned int size,
    CubeData cube_data)
    : size(size),
      cube_data(cube_data)
{
    needs_update();
}

void gst::TextureCube::set_size(unsigned int size)
{
    this->size = { size };
    needs_update();
}

void gst::TextureCube::set_data(CubeFace face, TextureData const & data)
{
    cube_data[static_cast<int>(face)] = data;
    needs_update();
}

gst::TextureTarget gst::TextureCube::get_target() const
{
    return TextureTarget::TEXTURE_CUBE;
}

gst::Resolution gst::TextureCube::get_size() const
{
    return size;
}

gst::TextureData gst::TextureCube::get_data(CubeFace face) const
{
    return cube_data[static_cast<int>(face)];
}
