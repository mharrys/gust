#include "bufferimpl.hpp"

#include "shadoweddata.hpp"

gst::BufferImpl::BufferImpl(
    BufferTarget target,
    std::shared_ptr<ShadowedData> shadowed_data)
    : target(target),
      shadowed_data(shadowed_data),
      usage(DataUsage::STATIC)
{
}

void gst::BufferImpl::set_int(std::vector<int> const & data)
{
    shadowed_data->set_int(data);
    needs_update();
}

void gst::BufferImpl::set_uint(std::vector<unsigned int> const & data)
{
    shadowed_data->set_uint(data);
    needs_update();
}

void gst::BufferImpl::set_float(std::vector<float> const & data)
{
    shadowed_data->set_float(data);
    needs_update();
}

void gst::BufferImpl::set_vec2(std::vector<glm::vec2> const & data)
{
    shadowed_data->set_vec2(data);
    needs_update();
}

void gst::BufferImpl::set_vec3(std::vector<glm::vec3> const & data)
{
    shadowed_data->set_vec3(data);
    needs_update();
}

void gst::BufferImpl::set_vec4(std::vector<glm::vec4> const & data)
{
    shadowed_data->set_vec4(data);
    needs_update();
}

void gst::BufferImpl::set_usage(DataUsage usage)
{
    this->usage = usage;
}

gst::BufferTarget gst::BufferImpl::get_target() const
{
    return target;
}

gst::DataUsage gst::BufferImpl::get_usage() const
{
    return usage;
}

gst::ShadowedData & gst::BufferImpl::get_shadowed_data()
{
    return *shadowed_data;
}
