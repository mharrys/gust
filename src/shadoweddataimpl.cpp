#include "shadoweddataimpl.hpp"

gst::ShadowedDelete::ShadowedDelete()
    : type(DataType::NONE)
{
}

gst::ShadowedDelete::ShadowedDelete(DataType type)
    : type(type)
{
}

void gst::ShadowedDelete::operator()(void * p) const
{
    switch (type) {
    case DataType::NONE:
        // ignore
        break;
    case DataType::BOOL:
        delete static_cast<bool *>(p);
        break;
    case DataType::INT:
    case DataType::INT_ARRAY:
        delete static_cast<int *>(p);
        break;
    case DataType::UINT:
    case DataType::UINT_ARRAY:
        delete static_cast<unsigned int *>(p);
        break;
    case DataType::FLOAT:
    case DataType::FLOAT_ARRAY:
        delete static_cast<float *>(p);
        break;
    case DataType::VEC2:
    case DataType::VEC2_ARRAY:
        delete static_cast<glm::vec2 *>(p);
        break;
    case DataType::VEC3:
    case DataType::VEC3_ARRAY:
        delete static_cast<glm::vec3 *>(p);
        break;
    case DataType::VEC4:
    case DataType::VEC4_ARRAY:
        delete static_cast<glm::vec4 *>(p);
        break;
    case DataType::MAT3:
    case DataType::MAT3_ARRAY:
        delete static_cast<glm::mat3 *>(p);
        break;
    case DataType::MAT4:
    case DataType::MAT4_ARRAY:
        delete static_cast<glm::mat4 *>(p);
        break;
    case DataType::UCHAR_ARRAY:
        delete static_cast<unsigned char *>(p);
        break;
    }
}

gst::ShadowedDataImpl::ShadowedDataImpl()
    : type(DataType::NONE),
      count(0),
      size_bytes(0)
{
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(bool data)
{
    auto int_data = static_cast<int>(data);
    set_data<int>(&int_data, 1u, DataType::BOOL);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(int data)
{
    set_data<int>(&data, 1u, DataType::INT);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(unsigned int data)
{
    set_data<unsigned int>(&data, 1u, DataType::UINT);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(float data)
{
    set_data<float>(&data, 1u, DataType::FLOAT);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::vec2 const & data)
{
    set_glm_data<glm::vec2>({ data }, DataType::VEC2, 2);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::vec3 const & data)
{
    set_glm_data<glm::vec3>({ data }, DataType::VEC3, 3);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::vec4 const & data)
{
    set_glm_data<glm::vec4>({ data }, DataType::VEC4, 4);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::mat3 const & data)
{
    set_glm_data<glm::mat3>({ data }, DataType::MAT3, 9);
    return *this;
}

gst::ShadowedData & gst::ShadowedDataImpl::operator=(glm::mat4 const & data)
{
    set_glm_data<glm::mat4>({ data }, DataType::MAT4, 16);
    return *this;
}

void gst::ShadowedDataImpl::set_uchar(std::vector<unsigned char> const & data)
{
    set_uchar(&data[0], data.size());
}

void gst::ShadowedDataImpl::set_uchar(unsigned char const * data, unsigned int count)
{
    set_data<unsigned char>(data, count, DataType::UCHAR_ARRAY);
}

void gst::ShadowedDataImpl::set_int(std::vector<int> const & data)
{
    set_int(&data[0], data.size());
}

void gst::ShadowedDataImpl::set_int(int const * data, unsigned int count)
{
    set_data<int>(data, count, DataType::INT_ARRAY);
}

void gst::ShadowedDataImpl::set_uint(std::vector<unsigned int> const & data)
{
    set_uint(&data[0], data.size());
}

void gst::ShadowedDataImpl::set_uint(unsigned int const * data, unsigned int count)
{
    set_data<unsigned int>(data, count, DataType::UINT_ARRAY);
}

void gst::ShadowedDataImpl::set_float(std::vector<float> const & data)
{
    set_float(&data[0], data.size());
}

void gst::ShadowedDataImpl::set_float(float const * data, unsigned int count)
{
    set_data<float>(data, count, DataType::FLOAT_ARRAY);
}

void gst::ShadowedDataImpl::set_vec2(std::vector<glm::vec2> const & data)
{
    set_glm_data<glm::vec2>(data, DataType::VEC2_ARRAY, 2);
}

void gst::ShadowedDataImpl::set_vec3(std::vector<glm::vec3> const & data)
{
    set_glm_data<glm::vec3>(data, DataType::VEC3_ARRAY, 3);
}

void gst::ShadowedDataImpl::set_vec4(std::vector<glm::vec4> const & data)
{
    set_glm_data<glm::vec4>(data, DataType::VEC4_ARRAY, 4);
}

void gst::ShadowedDataImpl::set_mat3(std::vector<glm::mat3> const & data)
{
    set_glm_data<glm::mat3>(data, DataType::MAT3_ARRAY, 9);
}

void gst::ShadowedDataImpl::set_mat4(std::vector<glm::mat4> const & data)
{
    set_glm_data<glm::mat4>(data, DataType::MAT4_ARRAY, 16);
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
