#ifndef SHADOWEDDATAIMPL_HPP_INCLUDED
#define SHADOWEDDATAIMPL_HPP_INCLUDED

#include "shadoweddata.hpp"

#include <array>
#include <cstring>
#include <memory>

namespace gst
{
    class ShadowedDelete : public std::default_delete<void> {
    public:
        ShadowedDelete();
        ShadowedDelete(DataType type);
        void operator()(void * p) const;
    private:
        DataType type;
    };

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

        void set_uchar(std::vector<unsigned char> const & data) final;
        void set_uchar(unsigned char const * data, unsigned int count) final;
        void set_int(std::vector<int> const & data) final;
        void set_int(int const * data, unsigned int count) final;
        void set_uint(std::vector<unsigned int> const & data) final;
        void set_uint(unsigned int const * data, unsigned int count) final;
        void set_float(std::vector<float> const & data) final;
        void set_float(float const * data, unsigned int count) final;
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
        void set_data(T const * new_data, unsigned int new_count, DataType new_type);
        template<typename T>
        void set_glm_data(std::vector<T> const & new_data, DataType new_type, unsigned int components);

        DataType type;
        unsigned int count;
        unsigned int size_bytes;
        std::unique_ptr<void, ShadowedDelete> data;
    };
}

template<typename T>
void gst::ShadowedDataImpl::set_data(T const * new_data, unsigned int new_count, DataType new_type)
{
    const auto new_size_bytes = new_count * sizeof(T);
    if (need_new_storage(new_type, new_count, new_size_bytes)) {
        type = new_type;
        count = new_count;
        size_bytes = new_size_bytes;
        data = std::unique_ptr<void, ShadowedDelete>(
            new T[count],
            ShadowedDelete(new_type)
        );
    }
    std::memcpy(data.get(), new_data, size_bytes);
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
        data = std::unique_ptr<void, ShadowedDelete>(
            new float[count * components],
            ShadowedDelete(new_type)
        );
    }
    std::memcpy(data.get(), &new_data[0], size_bytes);
}

#endif
