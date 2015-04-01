#ifndef SHADOWEDDATA_HPP_INCLUDED
#define SHADOWEDDATA_HPP_INCLUDED

#include "glm.hpp"

#include <memory>
#include <vector>

namespace gst
{
    // Supported shadowed data types.
    enum class DataType {
        NONE,
        BOOL,
        INT,
        UINT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
        MAT3,
        MAT4,
        UCHAR_ARRAY,
        INT_ARRAY,
        UINT_ARRAY,
        FLOAT_ARRAY,
        VEC2_ARRAY,
        VEC3_ARRAY,
        VEC4_ARRAY,
        MAT3_ARRAY,
        MAT4_ARRAY
    };

    // The responsibility of this class is to store data types with a single
    // data structure that can be changed at runtime.
    class ShadowedData {
    public:
        virtual ~ShadowedData() = default;
        // Set shadowed data to bool value.
        virtual ShadowedData & operator=(bool data) = 0;
        // Set shadowed data to int value.
        virtual ShadowedData & operator=(int data) = 0;
        // Set shadowed data to unsigned int value.
        virtual ShadowedData & operator=(unsigned int data) = 0;
        // Set shadowed data to float value.
        virtual ShadowedData & operator=(float data) = 0;
        // Set shadowed data to vec2 value.
        virtual ShadowedData & operator=(glm::vec2 const & data) = 0;
        // Set shadowed data to vec3 value.
        virtual ShadowedData & operator=(glm::vec3 const & data) = 0;
        // Set shadowed data to vec4 value.
        virtual ShadowedData & operator=(glm::vec4 const & data) = 0;
        // Set shadowed data to mat3 value.
        virtual ShadowedData & operator=(glm::mat3 const & data) = 0;
        // Set shadowed data to mat4 value.
        virtual ShadowedData & operator=(glm::mat4 const & data) = 0;
        // Set shadowed data to vector of unsigned char values.
        virtual void set_uchar(std::vector<unsigned char> const & data) = 0;
        // Set shadowed data to array of unsigned char values.
        virtual void set_uchar(unsigned char const * data, unsigned int count) = 0;
        // Set shadowed data to vector of int values.
        virtual void set_int(std::vector<int> const & data) = 0;
        // Set shadowed data to array of int values.
        virtual void set_int(int const * data, unsigned int count) = 0;
        // Set shadowed data to vector of unsigned int values.
        virtual void set_uint(std::vector<unsigned int> const & data) = 0;
        // Set shadowed data to array of unsigned int values.
        virtual void set_uint(unsigned int const * data, unsigned int count) = 0;
        // Set shadowed data to vector of float values.
        virtual void set_float(std::vector<float> const & data) = 0;
        // Set shadowed data to array of float values.
        virtual void set_float(float const * data, unsigned int count) = 0;
        // Set shadowed data to vector of vec2 values.
        virtual void set_vec2(std::vector<glm::vec2> const & data) = 0;
        // Set shadowed data to vector of vec3 values.
        virtual void set_vec3(std::vector<glm::vec3> const & data) = 0;
        // Set shadowed data to vector of vec4 values.
        virtual void set_vec4(std::vector<glm::vec4> const & data) = 0;
        // Set shadowed data to vector of mat3 values.
        virtual void set_mat3(std::vector<glm::mat3> const & data) = 0;
        // Set shadowed data to vector of mat4 values.
        virtual void set_mat4(std::vector<glm::mat4> const & data) = 0;
        // Return data type for current shadowed data.
        virtual DataType get_type() const = 0;
        // Return number of elements that is stored of current data type.
        virtual unsigned int get_count() const = 0;
        // Return size of shadowed data in bytes.
        virtual unsigned int get_size_bytes() const = 0;
        // Return shadowed data.
        virtual void const * get_data() const = 0;
    };
}

#endif
