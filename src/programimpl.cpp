#include "programimpl.hpp"

#include "annotationformatter.hpp"
#include "logger.hpp"
#include "shaderimpl.hpp"
#include "uniformcollection.hpp"

gst::ProgramImpl::ProgramImpl(std::shared_ptr<GraphicsDevice> device, std::shared_ptr<Logger> logger)
    : handle(device->create_program()),
      device(device),
      logger(logger),
      link_status(false),
      link_error("")
{
}

gst::ProgramImpl::~ProgramImpl()
{
    device->destroy_program(handle);
}

void gst::ProgramImpl::sync(UniformCollection const & uniforms, AnnotationFormatter const & formatter)
{
    for (auto & uniform : uniforms.get_uniforms()) {
        const auto annotation = formatter.format(uniform.first);
        const auto data = uniform.second;

        if (!data) {
            logger->log(TRACE("attempted to update uniform \"" + annotation + "\" with no allocated data"));
            return;
        }

        const auto location = get_cached_location(annotation);
        float * raw_data;

        switch (data.get_type()) {
        case UniformType::BOOL:
            device->uniform1i(location, *data.get_bool());
            break;
        case UniformType::INT:
            device->uniform1i(location, *data.get_int());
            break;
        case UniformType::FLOAT:
            device->uniform1f(location, *data.get_float());
            break;
        case UniformType::FLOAT_ARRAY:
            raw_data = data.get_float().get();
            device->uniform1fv(location, data.get_count(), raw_data);
            break;
        case UniformType::VEC2:
            raw_data = data.get_float().get();
            device->uniform2f(location, raw_data[0], raw_data[1]);
            break;
        case UniformType::VEC3:
            raw_data = data.get_float().get();
            device->uniform3f(location, raw_data[0], raw_data[1], raw_data[2]);
            break;
        case UniformType::VEC4:
            raw_data = data.get_float().get();
            device->uniform4f(location, raw_data[0], raw_data[1], raw_data[2], raw_data[3]);
            break;
        case UniformType::MAT3:
            raw_data = data.get_float().get();
            device->uniform_matrix3fv(location, 1, false, raw_data);
            break;
        case UniformType::MAT4:
            raw_data = data.get_float().get();
            device->uniform_matrix4fv(location, 1, false, raw_data);
            break;
        }
    }
}

void gst::ProgramImpl::attach(ShaderImpl & shader)
{
    device->attach_shader(handle, shader.handle);
}

void gst::ProgramImpl::detach(ShaderImpl & shader)
{
    device->detach_shader(handle, shader.handle);
}

void gst::ProgramImpl::bind_attribute(int index, std::string const & name)
{
    device->bind_attribute_location(handle, index, name);
}

void gst::ProgramImpl::link()
{
    device->link_program(handle);
    link_status = device->get_link_status(handle);
    link_error = link_status ? "" : device->get_link_error(handle);
}

bool gst::ProgramImpl::get_link_status() const
{
    return link_status;
}

std::string gst::ProgramImpl::get_link_error() const
{
    return link_error;
}

void gst::ProgramImpl::use()
{
    device->use_program(handle);
}

int gst::ProgramImpl::get_cached_location(std::string const & name)
{
    if (locations.count(name) == 0) {
        locations[name] = device->get_uniform_location(handle, name);
        if (locations[name] == -1) {
            logger->log(TRACE("could not get uniform location for \"" + name + "\""));
        }
    }
    return locations.at(name);
}
