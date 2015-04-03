#include "texture2d.hpp"

#include "image.hpp"
#include "shadoweddataimpl.hpp"

gst::Texture2D gst::Texture2D::create_empty(Resolution size)
{
    auto data = std::unique_ptr<ShadowedData>(new ShadowedDataImpl());
    return Texture2D(size, std::move(data));
}

gst::Texture2D gst::Texture2D::create_from_image(Image const & image)
{
    auto size = image.get_size();
    auto alpha = image.get_components() == 4;
    auto type = image.get_data().get_type();
    auto count = image.get_data().get_count();

    auto data = std::unique_ptr<ShadowedData>(new ShadowedDataImpl());
    if (type == DataType::UCHAR_ARRAY) {
        data->set_uchar(image.get_uchar_pixels(), count);
    } else {
        data->set_float(image.get_float_pixels(), count);
    }

    auto texture = Texture2D(size, std::move(data));
    if (alpha) {
        texture.set_internal_format(TextureFormat::RGBA);
        texture.set_source_format(PixelFormat::RGBA);
    }

    return texture;
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
