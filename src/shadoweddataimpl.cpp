#include "shadoweddataimpl.hpp"

gst::ShadowedDataImpl::ShadowedDataImpl()
    : type(DataType::NONE),
      count(0),
      size_bytes(0),
      data(nullptr)
{
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(bool data)
{
    set_bool(data);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(int data)
{
    set_int(data);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(float data)
{
    set_float(data);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::vec2 const & data)
{
    set_vec2(data);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::vec3 const & data)
{
    set_vec3(data);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::vec4 const & data)
{
    set_vec4(data);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::mat3 const & data)
{
    set_mat3(data);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::mat4 const & data)
{
    set_mat4(data);
    return *this;
}

void gst::ShadowedDataImpl::set_bool(bool data)
{
    set_data<int>({ static_cast<int>(data) }, DataType::BOOL);
}

void gst::ShadowedDataImpl::set_int(int data)
{
    set_data<int>({ data }, DataType::INT);
}

void gst::ShadowedDataImpl::set_unsigned_int(unsigned int data)
{
    set_data<unsigned int>({ data }, DataType::UNSIGNED_INT);
}

void gst::ShadowedDataImpl::set_float(float data)
{
    set_data<float>({ data }, DataType::FLOAT);
}

void gst::ShadowedDataImpl::set_vec2(glm::vec2 const & data)
{
    set_glm_data<glm::vec2>({ data }, DataType::VEC2, 2);
}

void gst::ShadowedDataImpl::set_vec3(glm::vec3 const & data)
{
    set_glm_data<glm::vec3>({ data }, DataType::VEC3, 3);
}

void gst::ShadowedDataImpl::set_vec4(glm::vec4 const & data)
{
    set_glm_data<glm::vec4>({ data }, DataType::VEC4, 4);
}

void gst::ShadowedDataImpl::set_mat3(glm::mat3 const & data)
{
    set_glm_data<glm::mat3>({ data }, DataType::MAT3, 9);
}

void gst::ShadowedDataImpl::set_mat4(glm::mat4 const & data)
{
    set_glm_data<glm::mat4>({ data }, DataType::MAT4, 16);
}

void gst::ShadowedDataImpl::set_unsigned_char_array(std::vector<unsigned char> const & array_data)
{
    set_data<unsigned char>(array_data, DataType::UNSIGNED_CHAR_ARRAY);
}

void gst::ShadowedDataImpl::set_int_array(std::vector<int> const & array_data)
{
    set_data<int>(array_data, DataType::INT_ARRAY);
}

void gst::ShadowedDataImpl::set_unsigned_int_array(std::vector<unsigned int> const & array_data)
{
    set_data<unsigned int>(array_data, DataType::UNSIGNED_INT_ARRAY);
}

void gst::ShadowedDataImpl::set_float_array(std::vector<float> const & array_data)
{
    set_data<float>(array_data, DataType::FLOAT_ARRAY);
}

void gst::ShadowedDataImpl::set_vec2_array(std::vector<glm::vec2> const & array_data)
{
    set_glm_data<glm::vec2>(array_data, DataType::VEC2_ARRAY, 2);
}

void gst::ShadowedDataImpl::set_vec3_array(std::vector<glm::vec3> const & array_data)
{
    set_glm_data<glm::vec3>(array_data, DataType::VEC3_ARRAY, 3);
}

void gst::ShadowedDataImpl::set_vec4_array(std::vector<glm::vec4> const & array_data)
{
    set_glm_data<glm::vec4>(array_data, DataType::VEC4_ARRAY, 4);
}

void gst::ShadowedDataImpl::set_mat3_array(std::vector<glm::mat3> const & array_data)
{
    set_glm_data<glm::mat3>(array_data, DataType::MAT3_ARRAY, 9);
}

void gst::ShadowedDataImpl::set_mat4_array(std::vector<glm::mat4> const & array_data)
{
    set_glm_data<glm::mat4>(array_data, DataType::MAT4_ARRAY, 16);
}

gst::DataType gst::ShadowedDataImpl::get_type() const
{
    return type;
}

unsigned int gst::ShadowedDataImpl::get_count() const
{
    return count;
}

unsigned int gst::ShadowedDataImpl::get_size_bytes() const
{
    return size_bytes;
}

void const * gst::ShadowedDataImpl::get_data() const
{
    return data.get();
}

bool gst::ShadowedDataImpl::need_new_storage(DataType type, unsigned int count, unsigned int size_bytes)
{
    return !data || this->type != type || this->count != count || this->size_bytes != size_bytes;
}
