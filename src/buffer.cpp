#include "buffer.hpp"

#include "bufferimpl.hpp"

#include <cstring>

gst::Buffer::Buffer(BufferTarget target)
    : impl(std::make_shared<BufferImpl>(target)),
      usage(DataUsage::STATIC),
      count(0),
      bytes(0),
      dirty(false)
{
}

bool gst::Buffer::operator==(Buffer const & other)
{
    return type == other.type && shadowed_data == other.shadowed_data;
}

bool gst::Buffer::operator!=(Buffer const & other)
{
    return !(*this == other);
}

gst::Buffer::operator bool() const
{
    return impl && shadowed_data;
}

void gst::Buffer::set_usage(DataUsage usage)
{
    this->usage = usage;
}

void gst::Buffer::set_int(std::vector<int> const & data)
{
    if (need_new_storage(DataType::INT, data.size())) {
        type = DataType::INT;
        count = data.size();
        bytes = sizeof(int) * count;
        shadowed_data = std::shared_ptr<int>(new int[count]);
    }
    std::memcpy(shadowed_data.get(), &data[0], bytes);
    dirty = true;
}

void gst::Buffer::set_uint(std::vector<unsigned int> const & data)
{
    if (need_new_storage(DataType::UNSIGNED_INT, data.size())) {
        type = DataType::UNSIGNED_INT;
        count = data.size();
        bytes = sizeof(unsigned int) * count;
        shadowed_data = std::shared_ptr<unsigned int>(new unsigned int[count]);
    }
    std::memcpy(shadowed_data.get(), &data[0], bytes);
    dirty = true;
}

void gst::Buffer::set_float(std::vector<float> const & data)
{
    if (need_new_storage(DataType::FLOAT, data.size())) {
        type = DataType::FLOAT;
        count = data.size();
        bytes = sizeof(float) * count;
        shadowed_data = std::shared_ptr<float>(new float[count]);
    }
    std::memcpy(shadowed_data.get(), &data[0], bytes);
    dirty = true;
}

void gst::Buffer::set_vec2(std::vector<glm::vec2> const & data)
{
    if (need_new_storage(DataType::VEC2, data.size())) {
        type = DataType::VEC2;
        count = data.size();
        bytes = sizeof(float) * 2 * count;
        shadowed_data = std::shared_ptr<glm::vec2>(new glm::vec2[count]);
    }
    std::memcpy(shadowed_data.get(), &data[0], bytes);
    dirty = true;
}

void gst::Buffer::set_vec3(std::vector<glm::vec3> const & data)
{
    if (need_new_storage(DataType::VEC3, data.size())) {
        type = DataType::VEC3;
        count = data.size();
        bytes = sizeof(float) * 3 * count;
        shadowed_data = std::shared_ptr<glm::vec3>(new glm::vec3[count]);
    }
    std::memcpy(shadowed_data.get(), &data[0], bytes);
    dirty = true;
}

void gst::Buffer::set_vec4(std::vector<glm::vec4> const & data)
{
    if (need_new_storage(DataType::VEC4, data.size())) {
        type = DataType::VEC4;
        count = data.size();
        bytes = sizeof(float) * 4 * count;
        shadowed_data = std::shared_ptr<glm::vec4>(new glm::vec4[count]);
    }
    std::memcpy(shadowed_data.get(), &data[0], bytes);
    dirty = true;
}

gst::DataType gst::Buffer::get_type() const
{
    return type;
}

size_t gst::Buffer::get_count() const
{
    return count;
}

bool gst::Buffer::need_new_storage(DataType type, size_t count)
{
    return !shadowed_data || this->type != type || this->count != count;
}

void gst::Buffer::refresh()
{
    if (dirty) {
        dirty = false;
        impl->buffer_data(bytes, shadowed_data.get(), usage);
    }
}
