#include "shaderimpl.hpp"

gst::ShaderImpl::ShaderImpl(std::shared_ptr<GraphicsDevice> device, ShaderType type)
    : handle(device->create_shader(type)),
      device(device),
      type(type),
      compile_status(false),
      compile_error("")
{
}

gst::ShaderImpl::~ShaderImpl()
{
    device->destroy_shader(handle);
}

gst::ShaderType gst::ShaderImpl::get_type() const
{
    return type;
}

gst::ShaderHandle gst::ShaderImpl::get_handle() const
{
    return handle;
}

void gst::ShaderImpl::compile(std::string const & source)
{
    device->compile_shader(handle, source);
    compile_status = device->get_compile_status(handle);
    compile_error = compile_status ? "" : device->get_compile_error(handle);
}

bool gst::ShaderImpl::get_compile_status() const
{
    return compile_status;
}

std::string gst::ShaderImpl::get_compile_error() const
{
    return compile_error;
}
