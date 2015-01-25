#include "textureimpl.hpp"

gst::TextureImpl::TextureImpl(TextureTarget target)
{
    glGenBuffers(1, &id);
    this->target = translator.translate(target);
}

gst::TextureImpl::~TextureImpl()
{
    glDeleteTextures(1, &id);
}

void gst::TextureImpl::image2D(Image const & image)
{
    auto size = image.get_size();

    glTexImage2D(
        target,
        0,
        internal_format,
        size.get_width(),
        size.get_height(),
        0,
        source_format,
        GL_UNSIGNED_BYTE,
        &image.get_data()[0]
    );
}

void gst::TextureImpl::parameter(TextureParam const & param)
{
    translate(param);
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, mag_filter);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap_s);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap_t);
}

void gst::TextureImpl::bind(int unit)
{
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(target, id);
}

void gst::TextureImpl::translate(TextureParam const & param)
{
    target = translator.translate(param.target);
    internal_format = translator.translate(param.internal_format);
    source_format = translator.translate(param.source_format);
    min_filter = translator.translate(param.min_filter);
    mag_filter = translator.translate(param.mag_filter);
    wrap_s = translator.translate(param.wrap_s);
    wrap_t = translator.translate(param.wrap_t);
}
