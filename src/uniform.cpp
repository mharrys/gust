#include "uniform.hpp"

#include <array>
#include <cstring>

gst::Uniform::Uniform(std::string name)
    : name(name),
      array_name(""),
      array_index(0),
      type(UniformType::BOOL),
      shadowed_data(nullptr),
      count(0),
      bytes(0)
{
}

gst::Uniform::Uniform(std::string name, bool value)
    : name(name),
      array_name(""),
      array_index(0)
{
    set_data(value);
}

gst::Uniform::Uniform(std::string name, int value)
    : name(name),
      array_name(""),
      array_index(0)
{
    set_data(value);
}

gst::Uniform::Uniform(std::string name, float value)
    : name(name),
      array_name(""),
      array_index(0)
{
    set_data(value);
}

gst::Uniform::Uniform(std::string name, std::vector<float> const & value)
    : name(name),
      array_name(""),
      array_index(0)
{
    set_data(value);
}

gst::Uniform::Uniform(std::string name, glm::vec2 const & value)
    : name(name),
      array_name(""),
      array_index(0)
{
    set_data(value);
}

gst::Uniform::Uniform(std::string name, glm::vec3 const & value)
    : name(name),
      array_name(""),
      array_index(0)
{
    set_data(value);
}

gst::Uniform::Uniform(std::string name, glm::vec4 const & value)
    : name(name),
      array_name(""),
      array_index(0)
{
    set_data(value);
}

gst::Uniform::Uniform(std::string name, glm::mat3 const & value)
    : name(name),
      array_name(""),
      array_index(0)
{
    set_data(value);
}

gst::Uniform::Uniform(std::string name, glm::mat4 const & value)
    : name(name),
      array_name(""),
      array_index(0)
{
    set_data(value);
}

bool gst::Uniform::operator==(Uniform const & other)
{
    return name == other.name &&
           type == other.type &&
           shadowed_data == other.shadowed_data;
}

bool gst::Uniform::operator!=(Uniform const & other)
{
    return !(*this == other);
}

gst::Uniform & gst::Uniform::operator=(bool value)
{
    set_data(value);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(int value)
{
    set_data(value);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(float value)
{
    set_data(value);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(std::vector<float> const & value)
{
    set_data(value);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::vec2 const & value)
{
    set_data(value);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::vec3 const & value)
{
    set_data(value);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::vec4 const & value)
{
    set_data(value);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::mat3 const & value)
{
    set_data(value);
    return *this;
}

gst::Uniform & gst::Uniform::operator=(glm::mat4 const & value)
{
    set_data(value);
    return *this;
}

void gst::Uniform::set_data(bool value)
{
    if (need_new_storage(UniformType::BOOL, 1)) {
        type = UniformType::BOOL;
        count = 1;
        bytes = sizeof(bool) * count;
        shadowed_data = std::make_shared<bool>();
    }
    std::memcpy(shadowed_data.get(), &value, bytes);
}

void gst::Uniform::set_data(int value)
{
    if (need_new_storage(UniformType::INT, 1)) {
        type = UniformType::INT;
        count = 1;
        bytes = sizeof(int) * count;
        shadowed_data = std::make_shared<int>();
    }
    std::memcpy(shadowed_data.get(), &value, bytes);
}

void gst::Uniform::set_data(float value)
{
    if (need_new_storage(UniformType::FLOAT, 1)) {
        type = UniformType::FLOAT;
        count = 1;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<float>();
    }
    std::memcpy(shadowed_data.get(), &value, bytes);
}

void gst::Uniform::set_data(std::vector<float> const & value)
{
    if (need_new_storage(UniformType::FLOAT_ARRAY, value.size())) {
        type = UniformType::FLOAT_ARRAY;
        count = value.size();
        bytes = sizeof(float) * count;
        shadowed_data = std::shared_ptr<float>(new float[count]);
    }
    std::memcpy(shadowed_data.get(), &value[0], bytes);
}

void gst::Uniform::set_data(glm::vec2 const & value)
{
    if (need_new_storage(UniformType::VEC2, 2)) {
        type = UniformType::VEC2;
        count = 2;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 2>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(value), bytes);
}

void gst::Uniform::set_data(glm::vec3 const & value)
{
    if (need_new_storage(UniformType::VEC3, 3)) {
        type = UniformType::VEC3;
        count = 3;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 3>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(value), bytes);
}

void gst::Uniform::set_data(glm::vec4 const & value)
{
    if (need_new_storage(UniformType::VEC4, 4)) {
        type = UniformType::VEC4;
        count = 4;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 4>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(value), bytes);
}

void gst::Uniform::set_data(glm::mat3 const & value)
{
    if (need_new_storage(UniformType::MAT3, 9)) {
        type = UniformType::MAT3;
        count = 9;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 9>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(value), bytes);
}

void gst::Uniform::set_data(glm::mat4 const & value)
{
    if (need_new_storage(UniformType::MAT4, 16)) {
        type = UniformType::MAT4;
        count = 16;
        bytes = sizeof(float) * count;
        shadowed_data = std::make_shared<std::array<float, 16>>();
    }
    std::memcpy(shadowed_data.get(), glm::value_ptr(value), bytes);
}

void gst::Uniform::set_name(std::string name)
{
    this->name = name;
}

void gst::Uniform::set_array_name(std::string array_name)
{
    this->array_name = array_name;
}

void gst::Uniform::set_array_index(unsigned int array_index)
{
    this->array_index= array_index;
}

std::string gst::Uniform::get_name() const
{
    return name;
}

std::string gst::Uniform::get_array_name() const
{
    if (array_name.empty()) {
        return name;
    } else {
        return array_name + "[" + std::to_string(array_index) + "]." + name;
    }
}

bool gst::Uniform::need_new_storage(UniformType type, size_t count)
{
    return !shadowed_data || this->type != type || this->count != count;
}
