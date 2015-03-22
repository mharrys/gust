#include "texture2d.hpp"

gst::Texture2D::Texture2D(Resolution size)
    : Texture2D(size, {})
{
}

gst::Texture2D::Texture2D(
    Resolution size,
    TextureData const & data)
    : size(size),
      data(data)
{
    needs_update();
}

void gst::Texture2D::set_size(Resolution size)
{
    this->size = size;
    needs_update();
}

void gst::Texture2D::set_data(TextureData const & data)
{
    this->data = data;
    needs_update();
}

gst::TextureTarget gst::Texture2D::get_target() const
{
    return TextureTarget::TEXTURE_2D;
}

gst::Resolution gst::Texture2D::get_size() const
{
    return size;
}

gst::TextureData gst::Texture2D::get_data() const
{
    return data;
}
