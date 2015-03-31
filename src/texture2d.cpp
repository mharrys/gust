#include "texture2d.hpp"

#include "shadoweddataimpl.hpp"

gst::Texture2D gst::Texture2D::create_empty(Resolution size)
{
    auto data = std::unique_ptr<ShadowedData>(new ShadowedDataImpl());
    return Texture2D(size, std::move(data));
}

gst::Texture2D::Texture2D(Resolution size, std::unique_ptr<ShadowedData> data)
    : size(size),
      data(std::move(data))
{
    needs_update();
}

void gst::Texture2D::set_size(Resolution size)
{
    this->size = size;
    needs_update();
}

void gst::Texture2D::set_data(std::unique_ptr<ShadowedData> data)
{
    this->data = std::move(data);
    needs_update();
}

gst::ShadowedData & gst::Texture2D::update_data()
{
    needs_update();
    return *data;
}

gst::TextureTarget gst::Texture2D::get_target() const
{
    return TextureTarget::TEXTURE_2D;
}

gst::Resolution gst::Texture2D::get_size() const
{
    return size;
}

gst::ShadowedData const & gst::Texture2D::get_data() const
{
    return *data;
}
