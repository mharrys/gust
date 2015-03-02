#include "shaderimpl.hpp"

gst::ShaderImpl::ShaderImpl(ShaderType type, std::string source)
    : type(type),
      source(source)
{
    needs_update();
}

gst::ShaderType gst::ShaderImpl::get_type() const
{
    return type;
}

std::string gst::ShaderImpl::get_source() const
{
    return source;
}
