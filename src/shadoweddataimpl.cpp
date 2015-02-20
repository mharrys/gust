#include "shadoweddataimpl.hpp"

gst::ShadowedDataImpl::ShadowedDataImpl()
    : data(nullptr),
      type(DataType::NONE),
      count(0),
      size_bytes(0)
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
    set_data<bool>(data, DataType::BOOL);
}

void gst::ShadowedDataImpl::set_int(int data)
{
    set_data<int>(data, DataType::INT);
}

void gst::ShadowedDataImpl::set_unsigned_int(unsigned int data)
{
    set_data<unsigned int>(data, DataType::UNSIGNED_INT);
}

void gst::ShadowedDataImpl::set_float(float data)
{
    set_data<float>(data, DataType::FLOAT);
}

void gst::ShadowedDataImpl::set_vec2(glm::vec2 const & data)
{
    set_array_data<float>({ data[0], data[1] }, DataType::VEC2);
}

void gst::ShadowedDataImpl::set_vec3(glm::vec3 const & data)
{
    set_array_data<float>({ data[0], data[1], data[2] }, DataType::VEC3);
}

void gst::ShadowedDataImpl::set_vec4(glm::vec4 const & data)
{
    set_array_data<float>({ data[0], data[1], data[2], data[3] }, DataType::VEC4);
}

void gst::ShadowedDataImpl::set_mat3(glm::mat3 const & data)
{
    set_array_data<float>(
        {
            data[0][0], data[0][1], data[0][2],
            data[1][0], data[1][1], data[1][2],
            data[2][0], data[2][1], data[2][2],
        },
        DataType::MAT3
    );
}

void gst::ShadowedDataImpl::set_mat4(glm::mat4 const & data)
{
    set_array_data<float>(
        {
            data[0][0], data[0][1], data[0][2], data[0][3],
            data[1][0], data[1][1], data[1][2], data[1][3],
            data[2][0], data[2][1], data[2][2], data[2][3],
            data[3][0], data[3][1], data[3][2], data[3][3],
        },
        DataType::MAT4
    );
}

void gst::ShadowedDataImpl::set_int_array(std::vector<int> const & array_data)
{
    set_array_data<int>(array_data, DataType::INT_ARRAY);
}

void gst::ShadowedDataImpl::set_unsigned_int_array(std::vector<unsigned int> const & array_data)
{
    set_array_data<unsigned int>(array_data, DataType::UNSIGNED_INT_ARRAY);
}

void gst::ShadowedDataImpl::set_float_array(std::vector<float> const & array_data)
{
    set_array_data<float>(array_data, DataType::FLOAT_ARRAY);
}

void gst::ShadowedDataImpl::set_vec2_array(std::vector<glm::vec2> const & array_data)
{
    set_vec_array<glm::vec2>(array_data, 2, DataType::VEC2_ARRAY);
}

void gst::ShadowedDataImpl::set_vec3_array(std::vector<glm::vec3> const & array_data)
{
    set_vec_array<glm::vec3>(array_data, 3, DataType::VEC3_ARRAY);
}

void gst::ShadowedDataImpl::set_vec4_array(std::vector<glm::vec4> const & array_data)
{
    set_vec_array<glm::vec4>(array_data, 4, DataType::VEC4_ARRAY);
}

bool gst::ShadowedDataImpl::get_bool() const
{
    return *std::static_pointer_cast<bool>(data);
}

int gst::ShadowedDataImpl::get_int() const
{
    return *std::static_pointer_cast<int>(data);
}

unsigned int gst::ShadowedDataImpl::get_unsigned_int() const
{
    return *std::static_pointer_cast<unsigned int>(data);
}

float gst::ShadowedDataImpl::get_float() const
{
    return *std::static_pointer_cast<float>(data);
}

glm::vec2 gst::ShadowedDataImpl::get_vec2() const
{
    return glm::make_vec2(&get_float_array()[0]);
}

glm::vec3 gst::ShadowedDataImpl::get_vec3() const
{
    return glm::make_vec3(&get_float_array()[0]);
}

glm::vec4 gst::ShadowedDataImpl::get_vec4() const
{
    return glm::make_vec4(&get_float_array()[0]);
}

glm::mat3 gst::ShadowedDataImpl::get_mat3() const
{
    return glm::make_mat3(&get_float_array()[0]);
}

glm::mat4 gst::ShadowedDataImpl::get_mat4() const
{
    return glm::make_mat4(&get_float_array()[0]);
}

std::vector<int> gst::ShadowedDataImpl::get_int_array() const
{
    return *std::static_pointer_cast<std::vector<int>>(data);
}

std::vector<unsigned int> gst::ShadowedDataImpl::get_unsigned_int_array() const
{
    return *std::static_pointer_cast<std::vector<unsigned int>>(data);
}

std::vector<float> gst::ShadowedDataImpl::get_float_array() const
{
    return *std::static_pointer_cast<std::vector<float>>(data);
}

std::vector<glm::vec2> gst::ShadowedDataImpl::get_vec2_array() const
{
    return get_vec_array<glm::vec2>(2);
}

std::vector<glm::vec3> gst::ShadowedDataImpl::get_vec3_array() const
{
    return get_vec_array<glm::vec3>(3);
}

std::vector<glm::vec4> gst::ShadowedDataImpl::get_vec4_array() const
{
    return get_vec_array<glm::vec4>(4);
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

bool gst::ShadowedDataImpl::need_new_storage(DataType type, unsigned int size_bytes)
{
    return !data || this->type != type || this->size_bytes != size_bytes;
}
