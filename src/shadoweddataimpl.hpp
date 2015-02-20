#ifndef SHADOWEDDATAIMPL_HPP_INCLUDED
#define SHADOWEDDATAIMPL_HPP_INCLUDED

#include "shadoweddata.hpp"

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

        void set_bool(bool bool_data);
        void set_int(int int_data);
        void set_unsigned_int(unsigned int int_data);
        void set_float(float float_data);
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

        bool get_bool() const;
        int get_int() const;
        unsigned int get_unsigned_int() const;
        float get_float() const;
        glm::vec2 get_vec2() const;
        glm::vec3 get_vec3() const;
        glm::vec4 get_vec4() const;
        glm::mat3 get_mat3() const;
        glm::mat4 get_mat4() const;

        std::vector<int> get_int_array() const;
        std::vector<unsigned int> get_unsigned_int_array() const;
        std::vector<float> get_float_array() const;
        std::vector<glm::vec2> get_vec2_array() const;
        std::vector<glm::vec3> get_vec3_array() const;
        std::vector<glm::vec4> get_vec4_array() const;

        DataType get_type() const;
        unsigned int get_count() const;
        unsigned int get_size_bytes() const;
        std::shared_ptr<void> get_raw_data() const;
    private:
        bool need_new_storage(DataType type, unsigned int size_bytes);
        template<typename T>
        void set_data(T const & new_data, DataType new_type);
        template<typename T>
        void set_array_data(std::vector<T> const & new_data, DataType new_type);
        template<typename T>
        void set_vec_array(std::vector<T> const & new_data, unsigned int components, DataType type);
        template<typename T>
        std::vector<T> get_vec_array(unsigned int components) const;

        std::shared_ptr<void> data;
        DataType type;
        unsigned int count;
        unsigned int size_bytes;
    };
}


template<typename T>
void gst::ShadowedDataImpl::set_data(T const & new_data, DataType new_type)
{
    const auto new_size_bytes = sizeof(T);
    if (need_new_storage(new_type, new_size_bytes)) {
        data = std::make_shared<T>(new_data);
        type = new_type;
        count = 1;
        size_bytes = new_size_bytes;
    } else {
        std::memcpy(data.get(), &new_data, size_bytes);
    }
}

template<typename T>
void gst::ShadowedDataImpl::set_array_data(std::vector<T> const & new_data, DataType new_type)
{
    const auto new_count = new_data.size();
    const auto new_size_bytes = sizeof(T) * new_count;
    if (need_new_storage(new_type, new_size_bytes)) {
        data = std::make_shared<std::vector<T>>(new_data);
        type = new_type;
        count = new_count;
        size_bytes = new_size_bytes;
    } else {
        auto & current = *std::static_pointer_cast<std::vector<T>>(data);
        std::memcpy(current.data(), new_data.data(), size_bytes);
    }
}

template<typename T>
void gst::ShadowedDataImpl::set_vec_array(std::vector<T> const & new_data, unsigned int components, DataType type)
{
    std::vector<float> v;
    v.reserve(components * new_data.size());
    for (auto data : new_data) {
        for (unsigned int i = 0; i < components; i++) {
            v.push_back(data[i]);
        }
    }
    set_array_data<float>(v, type);
}

template<typename T>
std::vector<T> gst::ShadowedDataImpl::get_vec_array(unsigned int components) const
{
    std::vector<T> result;
    auto v = get_float_array();
    for (unsigned int i = 0; i < v.size(); i += components) {
        T data;
        for (unsigned int j = 0; j < components; j++) {
            data[j] = v[i];
        }
        result.push_back(data);
    }
    return result;
}

#endif
