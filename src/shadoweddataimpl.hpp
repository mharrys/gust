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

        ShadowedData & operator=(bool data);
        ShadowedData & operator=(int data);
        ShadowedData & operator=(float data);
        ShadowedData & operator=(glm::vec2 const & data);
        ShadowedData & operator=(glm::vec3 const & data);
        ShadowedData & operator=(glm::vec4 const & data);
        ShadowedData & operator=(glm::mat3 const & data);
        ShadowedData & operator=(glm::mat4 const & data);

        void set_bool(bool data);
        void set_int(int data);
        void set_unsigned_int(unsigned int data);
        void set_float(float data);
        void set_vec2(glm::vec2 const & data);
        void set_vec3(glm::vec3 const & data);
        void set_vec4(glm::vec4 const & data);
        void set_mat3(glm::mat3 const & data);
        void set_mat4(glm::mat4 const & data);

        void set_int_array(std::vector<int> const & int_array_data);
        void set_unsigned_int_array(std::vector<unsigned int> const & int_array_data);
        void set_float_array(std::vector<float> const & float_array_data);
        void set_vec2_array(std::vector<glm::vec2> const & array_data);
        void set_vec3_array(std::vector<glm::vec3> const & array_data);
        void set_vec4_array(std::vector<glm::vec4> const & array_data);
        void set_mat3_array(std::vector<glm::mat3> const & array_data);
        void set_mat4_array(std::vector<glm::mat4> const & array_data);

        DataType get_type() const;
        unsigned int get_count() const;
        unsigned int get_size_bytes() const;
        void const * get_data() const;
    private:
        bool need_new_storage(DataType type, unsigned int count, unsigned int size_bytes);
        template<typename T>
        void set_data(std::vector<T> const & new_data, DataType new_type);
        template<typename T>
        void set_glm_data(std::vector<T> const & new_data, DataType new_type, unsigned int components);

        DataType type;
        unsigned int count;
        unsigned int size_bytes;
        std::shared_ptr<void> data;
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
        data = std::shared_ptr<T>(new T[count]);
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
        data = std::shared_ptr<float>(new float[count * components]);
    }
    std::memcpy(data.get(), &new_data[0], size_bytes);
}

#endif
