#include "texture.hpp"

#include "image.hpp"
#include "renderstate.hpp"
#include "textureimpl.hpp"

gst::Texture::Texture(
    std::shared_ptr<RenderState> render_state,
    Resolution size,
    std::vector<unsigned char> const & data,
    TextureParam const & param)
    : impl(std::make_shared<TextureImpl>(param.target)),
      render_state(render_state)
{
    push();
    impl->parameter(param);
    impl->image2D(size, data);
    pop();
}

gst::Texture::Texture(
    std::shared_ptr<RenderState> render_state,
    Image const & image,
    TextureParam const & param)
    : Texture(render_state, image.get_size(), image.get_data(), param)
{
}

bool gst::Texture::operator==(Texture const & other)
{
    return impl == other.impl;
}

bool gst::Texture::operator!=(Texture const & other)
{
    return !(*this == other);
}

gst::Texture::operator bool() const
{
    return impl != nullptr;
}

void gst::Texture::update(Resolution size, std::vector<unsigned char> const & data)
{
    push();
    impl->image2D(size, data);
    pop();
}

void gst::Texture::update(TextureParam const & param)
{
    push();
    impl->parameter(param);
    pop();
}

void gst::Texture::push()
{
    render_state->push();
    render_state->set_texture(*this);
}

void gst::Texture::pop()
{
    render_state->pop();
}
