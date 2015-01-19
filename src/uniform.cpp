#include "uniform.hpp"

#include <array>
#include <cstring>

gst::Uniform::Uniform(bool data)
{
    set_data(data);
}

gst::Uniform::Uniform(int data)
{
    set_data(data);
}

gst::Uniform::Uniform(float data)
{
    set_data(data);
}

gst::Uniform::Uniform(std::vector<float> const & data)
{
    set_data(data);
}

gst::Uniform::Uniform(glm::vec2 const & data)
{
    set_data(data);
}

gst::Uniform::Uniform(glm::vec3 const & data)
{
    set_data(data);
}

gst::Uniform::Uniform(glm::vec4 const & data)
{
    set_data(data);
}

gst::Uniform::Uniform(glm::mat3 const & data)
{
    set_data(data);
}

gst::Uniform::Uniform(glm::mat4 const & data)
{
    set_data(data);
}

bool gst::Uniform::operator==(Uniform const & other)
{
    return type == other.type && shadowed_data == other.shadowed_data;
}

bool gst::Uniform::operator!=(Uniform const & other)
{
    return !(*this == other);
}

gst::Uniform & gst::Uniform::operator=(bool data)
{
    set_data(data);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(int data)
{
    set_data(data);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(float data)
{
    set_data(data);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(std::vector<float> const & data)
{
    set_data(data);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::vec2 const & data)
{
    set_data(data);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::vec3 const & data)
{
    set_data(data);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::vec4 const & data)
{
    set_data(data);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::mat3 const & data)
{
    set_data(data);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::mat4 const & data)
{
    set_data(data);
    return *this;
}

void gst::Uniform::set_data(bool data)
{
    if (need_new_storage(UniformType::BOOL, 1)) {
        type = UniformType::BOOL;
        count = 1;
        bytes = sizeof(bool) * count;
        shadowed_data = std::make_shared<bool>();
    }
    std::memcpy(shadowed_data.get(), &data, bytes);
}

void gst::Uniform::set_data(int data)
{
    if (need_new_storage(UniformType::INT, 1)) {
        type = UniformType::INT;
        count = 1;
        bytes = sizeof(int) * count;
        shadowed_data = std::make_shared<int>();
    }
    std::memcpy(shadowed_data.get(), &data, bytes);
}

void gst::Uniform::set_data(float data)
{
    if (need_new_storage(UniformType::FLOAT, 1)) {
        type = UniformType::FLOAT;
        count = 1;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<float>();
    }
    std::memcpy(shadowed_data.get(), &data, bytes);
}

void gst::Uniform::set_data(std::vector<float> const & data)
{
    if (need_new_storage(UniformType::FLOAT_ARRAY, data.size())) {
        type = UniformType::FLOAT_ARRAY;
        count = data.size();
        bytes = sizeof(float) * count;
        shadowed_data = std::shared_ptr<float>(new float[count]);
    }
    std::memcpy(shadowed_data.get(), &data[0], bytes);
}

void gst::Uniform::set_data(glm::vec2 const & data)
{
    if (need_new_storage(UniformType::VEC2, 2)) {
        type = UniformType::VEC2;
        count = 2;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 2>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(data), bytes);
}

void gst::Uniform::set_data(glm::vec3 const & data)
{
    if (need_new_storage(UniformType::VEC3, 3)) {
        type = UniformType::VEC3;
        count = 3;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 3>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(data), bytes);
}

void gst::Uniform::set_data(glm::vec4 const & data)
{
    if (need_new_storage(UniformType::VEC4, 4)) {
        type = UniformType::VEC4;
        count = 4;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 4>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(data), bytes);
}

void gst::Uniform::set_data(glm::mat3 const & data)
{
    if (need_new_storage(UniformType::MAT3, 9)) {
        type = UniformType::MAT3;
        count = 9;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 9>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(data), bytes);
}

void gst::Uniform::set_data(glm::mat4 const & data)
{
    if (need_new_storage(UniformType::MAT4, 16)) {
        type = UniformType::MAT4;
        count = 16;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 16>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(data), bytes);
}

bool gst::Uniform::need_new_storage(UniformType type, size_t count)
{
    return !shadowed_data || this->type != type || this->count != count;
}
