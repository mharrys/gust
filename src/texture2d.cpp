#include "texture2d.hpp"

#include "image.hpp"

gst::Texture2d::Texture2d(
    std::shared_ptr<GraphicsDevice> device,
    Resolution size,
    std::vector<unsigned char> const & data,
    TextureParam const & param)
    : handle(device->create_texture()),
      device(device),
      target(TextureTarget::TEXTURE_2D),
      size(size),
      data(data),
      param(param),
      image_dirty(true),
      param_dirty(true)
{
}

gst::Texture2d::Texture2d(
    std::shared_ptr<GraphicsDevice> device,
    Image const & image,
    TextureParam const & param)
    : Texture2d(device, image.get_size(), image.get_data(), param)
{
}

gst::Texture2d::~Texture2d()
{
    device->destroy_texture(handle);
}

void gst::Texture2d::set_size(Resolution size)
{
    this->size = size;
    image_dirty = true;
}

void gst::Texture2d::set_data(std::vector<unsigned char> const & data)
{
    this->data = data;
    image_dirty = true;
}

void gst::Texture2d::set_image(Image const & image)
{
    set_size(image.get_size());
    set_data(image.get_data());
}

void gst::Texture2d::set_param(TextureParam const & param)
{
    this->param = param;
    param_dirty = true;
}

gst::TextureHandle gst::Texture2d::get_handle() const
{
    return handle;
}

void gst::Texture2d::bind(int unit)
{
    device->bind_texture(handle, target, unit);
}

void gst::Texture2d::sync()
{
    if (param_dirty) {
        param_dirty = false;
        device->texture_parameters(target, param);
    }

    if (image_dirty) {
        image_dirty = false;
        device->texture_image_2d(target, { size, data }, param);
    }
}
