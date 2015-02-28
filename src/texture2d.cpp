#include "texture2d.hpp"

#include "image.hpp"

gst::Texture2d::Texture2d(
    Resolution size,
    std::vector<unsigned char> const & data,
    TextureParam const & param)
    : size(size),
      data(data),
      param(param)
{
    needs_update();
}

void gst::Texture2d::set_size(Resolution size)
{
    this->size = size;
    needs_update();
}

void gst::Texture2d::set_data(std::vector<unsigned char> const & data)
{
    this->data = data;
    needs_update();
}

void gst::Texture2d::set_param(TextureParam const & param)
{
    this->param = param;
    needs_update();
}

gst::TextureTarget gst::Texture2d::get_target() const
{
    return TextureTarget::TEXTURE_2D;
}

gst::Resolution gst::Texture2d::get_size() const
{
    return size;
}

std::vector<unsigned char> gst::Texture2d::get_data() const
{
    return data;
}

gst::TextureParam gst::Texture2d::get_param() const
{
    return param;
}
