#include "bufferimpl.hpp"

#include "shadoweddata.hpp"

gst::BufferImpl::BufferImpl(std::shared_ptr<ShadowedData> shadowed_data)
    : target(BufferTarget::ELEMENT_ARRAY),
      shadowed_data(shadowed_data),
      usage(DataUsage::STATIC)
{
}

void gst::BufferImpl::set_int_array(std::vector<int> const & data)
{
    shadowed_data->set_int_array(data);
    needs_update();
}

void gst::BufferImpl::set_unsigned_int_array(std::vector<unsigned int> const & data)
{
    shadowed_data->set_unsigned_int_array(data);
    needs_update();
}

void gst::BufferImpl::set_float_array(std::vector<float> const & data)
{
    shadowed_data->set_float_array(data);
    needs_update();
}

void gst::BufferImpl::set_vec2_array(std::vector<glm::vec2> const & data)
{
    shadowed_data->set_vec2_array(data);
    needs_update();
}

void gst::BufferImpl::set_vec3_array(std::vector<glm::vec3> const & data)
{
    shadowed_data->set_vec3_array(data);
    needs_update();
}

void gst::BufferImpl::set_vec4_array(std::vector<glm::vec4> const & data)
{
    shadowed_data->set_vec4_array(data);
    needs_update();
}

void gst::BufferImpl::set_target(BufferTarget target)
{
    this->target = target;
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

std::shared_ptr<gst::ShadowedData> gst::BufferImpl::get_shadowed_data() const
{
    return shadowed_data;
}

unsigned int gst::BufferImpl::get_count() const
{
    return shadowed_data->get_count();
}

unsigned int gst::BufferImpl::get_size_bytes() const
{
    return shadowed_data->get_size_bytes();
}
