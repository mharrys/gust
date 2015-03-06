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
        UNSIGNED_INT,
        FLOAT,
        VEC2,
        VEC3,
        VEC4,
        MAT3,
        MAT4,
        INT_ARRAY,
        UNSIGNED_INT_ARRAY,
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
        // Set shadowed data to bool value.
        virtual void set_bool(bool data) = 0;
        // Set shadowed data to int value.
        virtual void set_int(int data) = 0;
        // Set shadowed data to unsigned int value.
        virtual void set_unsigned_int(unsigned int data) = 0;
        // Set shadowed data to float value.
        virtual void set_float(float data) = 0;
        // Set shadowed data to vec2 value.
        virtual void set_vec2(glm::vec2 const & data) = 0;
        // Set shadowed data to vec3 value.
        virtual void set_vec3(glm::vec3 const & data) = 0;
        // Set shadowed data to vec4 value.
        virtual void set_vec4(glm::vec4 const & data) = 0;
        // Set shadowed data to mat3 value.
        virtual void set_mat3(glm::mat3 const & data) = 0;
        // Set shadowed data to mat4 value.
        virtual void set_mat4(glm::mat4 const & data) = 0;
        // Set shadowed data to vector of int values.
        virtual void set_int_array(std::vector<int> const & array_data) = 0;
        // Set shadowed data to vector of unsigned int values.
        virtual void set_unsigned_int_array(std::vector<unsigned int> const & array_data) = 0;
        // Set shadowed data to vector of float values.
        virtual void set_float_array(std::vector<float> const & array_data) = 0;
        // Set shadowed data to vector of vec2 values.
        virtual void set_vec2_array(std::vector<glm::vec2> const & array_data) = 0;
        // Set shadowed data to vector of vec3 values.
        virtual void set_vec3_array(std::vector<glm::vec3> const & array_data) = 0;
        // Set shadowed data to vector of vec4 values.
        virtual void set_vec4_array(std::vector<glm::vec4> const & array_data) = 0;
        // Set shadowed data to vector of mat3 values.
        virtual void set_mat3_array(std::vector<glm::mat3> const & array_data) = 0;
        // Set shadowed data to vector of mat4 values.
        virtual void set_mat4_array(std::vector<glm::mat4> const & array_data) = 0;
        // Return data type for current shadowed data.
        virtual DataType get_type() const = 0;
        // Return number of elements that is stored of current data type.
        virtual unsigned int get_count() const = 0;
        // Return size of shadowed data in bytes.
        virtual unsigned int get_size_bytes() const = 0;
        // Return shadowed data.
        virtual std::shared_ptr<void> get_data() const = 0;
        // Return shadowed data interpreted as integer.
        virtual std::shared_ptr<int> get_as_int() const = 0;
        // Return shadowed data interpreted as unsigned integer.
        virtual std::shared_ptr<unsigned int> get_as_unsigned_int() const = 0;
        // Return shadowed data interpreted as float.
        virtual std::shared_ptr<float> get_as_float() const = 0;
    };
}

#endif
