#include "texturecube.hpp"

#include "shadoweddataimpl.hpp"

gst::TextureCube gst::TextureCube::create_empty(unsigned int size)
{
    CubeData cube_data;
    for (auto i = 0u; i < CUBE_FACES.size(); i++) {
        cube_data[i] = std::unique_ptr<ShadowedData>(new ShadowedDataImpl());
    }
    return TextureCube(size, std::move(cube_data));
}

gst::TextureCube::TextureCube(unsigned int size, CubeData cube_data)
    : size(size),
      cube_data(std::move(cube_data))
{
    needs_update();
}

void gst::TextureCube::set_size(unsigned int size)
{
    this->size = { size };
    needs_update();
}

void gst::TextureCube::set_data(CubeFace face, std::unique_ptr<ShadowedData> data)
{
    cube_data[static_cast<int>(face)] = std::move(data);
    needs_update();
}

gst::ShadowedData & gst::TextureCube::update_data(CubeFace face)
{
    needs_update();
    return *cube_data[static_cast<int>(face)];
}

gst::TextureTarget gst::TextureCube::get_target() const
{
    return TextureTarget::TEXTURE_CUBE;
}

gst::Resolution gst::TextureCube::get_size() const
{
    return size;
}

gst::ShadowedData const & gst::TextureCube::get_data(CubeFace face) const
{
    return *cube_data[static_cast<int>(face)];
}
