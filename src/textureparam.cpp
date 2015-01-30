#include "textureparam.hpp"

gst::TextureParam::TextureParam()
    : target(TextureTarget::TEXTURE_2D),
      internal_format(TextureFormat::RGB),
      source_format(PixelFormat::RGB),
      min_filter(FilterMode::LINEAR),
      mag_filter(FilterMode::LINEAR),
      wrap_s(WrapMode::REPEAT),
      wrap_t(WrapMode::REPEAT),
      depth_compare(CompareFunc::NONE)
{
}
