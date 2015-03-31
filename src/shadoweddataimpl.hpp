#ifndef SHADOWEDDATAIMPL_HPP_INCLUDED
#define SHADOWEDDATAIMPL_HPP_INCLUDED

#include "shadoweddata.hpp"

#include <array>
#include <cstring>
#include <memory>

namespace gst
{
    class ShadowedDataImpl : public ShadowedData {
    public:
        ShadowedDataImpl();

        ShadowedData & operator=(bool data) final;
        ShadowedData & operator=(int data) final;
        ShadowedData & operator=(unsigned int data) final;
        ShadowedData & operator=(float data) final;
        ShadowedData & operator=(glm::vec2 const & data) final;
        ShadowedData & operator=(glm::vec3 const & data) final;
        ShadowedData & operator=(glm::vec4 const & data) final;
        ShadowedData & operator=(glm::mat3 const & data) final;
        ShadowedData & operator=(glm::mat4 const & data) final;

        void set_uchar(std::vector<unsigned char> const & int_array_data) final;
        void set_int(std::vector<int> const & data) final;
        void set_uint(std::vector<unsigned int> const & data) final;
        void set_float(std::vector<float> const & data) final;
        void set_vec2(std::vector<glm::vec2> const & data) final;
        void set_vec3(std::vector<glm::vec3> const & data) final;
        void set_vec4(std::vector<glm::vec4> const & data) final;
        void set_mat3(std::vector<glm::mat3> const & data) final;
        void set_mat4(std::vector<glm::mat4> const & data) final;

        DataType get_type() const final;
        unsigned int get_count() const final;
        unsigned int get_size_bytes() const final;
        void const * get_data() const final;
    private:
        bool need_new_storage(DataType type, unsigned int count, unsigned int size_bytes);
        template<typename T>
        void set_data(std::vector<T> const & new_data, DataType new_type);
        template<typename T>
        void set_glm_data(std::vector<T> const & new_data, DataType new_type, unsigned int components);

        DataType type;
        unsigned int count;
        unsigned int size_bytes;
        std::unique_ptr<void> data;
    };
}

template<typename T>
void gst::ShadowedDataImpl::set_data(std::vector<T> const & new_data, DataType new_type)
{
    const auto new_count = new_data.size();
    const auto new_size_bytes = new_count * sizeof(T);
    if (need_new_storage(new_type, new_count, new_size_bytes)) {
        type = new_type;
        count = new_count;
        size_bytes = new_size_bytes;
        data = std::unique_ptr<T>(new T[count]);
    }
    std::memcpy(data.get(), &new_data[0], size_bytes);
}

template<typename T>
void gst::ShadowedDataImpl::set_glm_data(std::vector<T> const & new_data, DataType new_type, unsigned int components)
{
    const auto new_count = new_data.size();
    const auto new_size_bytes = new_count * sizeof(float) * components;
    if (need_new_storage(new_type, new_count, new_size_bytes)) {
        type = new_type;
        count = new_count;
        size_bytes = new_size_bytes;
        data = std::unique_ptr<float>(new float[count * components]);
    }
    std::memcpy(data.get(), &new_data[0], size_bytes);
}

#endif
