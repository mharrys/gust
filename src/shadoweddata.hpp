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
        VEC4_ARRAY
    };

    // The responsibility of this class is to store data types with a single
    // data structure. It must allow for changing the data types at runtime.
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
        // Return current shadowed data interpreted as bool value.
        virtual bool get_bool() const = 0;
        // Return current shadowed data interpreted as int value.
        virtual int get_int() const = 0;
        // Return current shadowed data interpreted as unsigned int value.
        virtual unsigned int get_unsigned_int() const = 0;
        // Return current shadowed data interpreted as float value.
        virtual float get_float() const = 0;
        // Return current shadowed data interpreted as vec2 value.
        virtual glm::vec2 get_vec2() const = 0;
        // Return current shadowed data interpreted as vec3 value.
        virtual glm::vec3 get_vec3() const = 0;
        // Return current shadowed data interpreted as vec4 value.
        virtual glm::vec4 get_vec4() const = 0;
        // Return current shadowed data interpreted as mat3 value.
        virtual glm::mat3 get_mat3() const = 0;
        // Return current shadowed data interpreted as mat4 value.
        virtual glm::mat4 get_mat4() const = 0;
        // Return current shadowed data interpreted as vector of int values.
        virtual std::vector<int> get_int_array() const = 0;
        // Return current shadowed data interpreted as vector of unsigned int values.
        virtual std::vector<unsigned int> get_unsigned_int_array() const = 0;
        // Return current shadowed data interpreted as vector of float values.
        virtual std::vector<float> get_float_array() const = 0;
        // Return current shadowed data interpreted as vector of vec2 values.
        virtual std::vector<glm::vec2> get_vec2_array() const = 0;
        // Return current shadowed data interpreted as vector of vec3 values.
        virtual std::vector<glm::vec3> get_vec3_array() const = 0;
        // Return current shadowed data interpreted as vector of vec4 values.
        virtual std::vector<glm::vec4> get_vec4_array() const = 0;
        // Return data type for current shadowed data.
        virtual DataType get_type() const = 0;
        // Return number of elements stored in shadowed data. Note for glm
        // data structure it is their internal number of elements that is counted
        // as well as the number of elements in an array.
        virtual unsigned int get_count() const = 0;
        // Return size of shadowed data in bytes.
        virtual unsigned int get_size_bytes() const = 0;
    };
}

#endif
