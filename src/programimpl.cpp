#include "programimpl.hpp"

#include "annotationformatter.hpp"
#include "logger.hpp"
#include "shader.hpp"
#include "shadoweddata.hpp"
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
        const auto location = get_cached_location(annotation);

        switch (data->get_type()) {
        case DataType::NONE:
            logger->log(TRACE("attempted to update uniform \"" + annotation + "\" with no allocated data"));
            break;
        case DataType::BOOL:
            device->uniform_int(location, data->get_bool());
            break;
        case DataType::INT:
            device->uniform_int(location, data->get_int());
            break;
        case DataType::FLOAT:
            device->uniform_float(location, data->get_float());
            break;
        case DataType::VEC2:
            device->uniform_vec2(location, data->get_vec2());
            break;
        case DataType::VEC3:
            device->uniform_vec3(location, data->get_vec3());
            break;
        case DataType::VEC4:
            device->uniform_vec4(location, data->get_vec4());
            break;
        case DataType::MAT3:
            device->uniform_matrix3(location, 1, false, data->get_float_array());
            break;
        case DataType::MAT4:
            device->uniform_matrix4(location, 1, false, data->get_float_array());
            break;
        case DataType::INT_ARRAY:
            device->uniform_int_array(location, data->get_int_array());
            break;
        case DataType::FLOAT_ARRAY:
            device->uniform_float_array(location, data->get_float_array());
            break;
        case DataType::UNSIGNED_INT:
        case DataType::UNSIGNED_INT_ARRAY:
        case DataType::VEC2_ARRAY:
        case DataType::VEC3_ARRAY:
        case DataType::VEC4_ARRAY:
            logger->log(TRACE("unsupported data type for uniform \"" + annotation + "\""));
            break;
        }
    }
}

void gst::ProgramImpl::attach(Shader const & shader)
{
    device->attach_shader(handle, shader.get_handle());
}

void gst::ProgramImpl::detach(Shader const & shader)
{
    device->detach_shader(handle, shader.get_handle());
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

int gst::ProgramImpl::get_cached_location(std::string const & annotation)
{
    if (locations.count(annotation) == 0) {
        locations[annotation] = device->get_uniform_location(handle, annotation);
        if (locations[annotation] == -1) {
            logger->log(TRACE("could not get uniform location for \"" + annotation + "\""));
        }
    }
    return locations.at(annotation);
}
