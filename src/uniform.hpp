#ifndef UNIFORM_HPP_INCLUDED
#define UNIFORM_HPP_INCLUDED

#include "glm.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Program;

    enum class UniformType {
        BOOL,
        INT,
        FLOAT,
        FLOAT_ARRAY,
        VEC2,
        VEC3,
        VEC4,
        MAT3,
        MAT4
    };

    class Uniform {
        friend Program;
    public:
        Uniform() = default;
        Uniform(bool data);
        Uniform(int data);
        Uniform(float data);
        Uniform(std::vector<float> const & data);
        Uniform(glm::vec2 const & data);
        Uniform(glm::vec3 const & data);
        Uniform(glm::vec4 const & data);
        Uniform(glm::mat3 const & data);
        Uniform(glm::mat4 const & data);

        bool operator==(Uniform const & other);
        bool operator!=(Uniform const & other);

        Uniform & operator=(bool data);
        Uniform & operator=(int data);
        Uniform & operator=(float data);
        Uniform & operator=(std::vector<float> const & data);
        Uniform & operator=(glm::vec2 const & data);
        Uniform & operator=(glm::vec3 const & data);
        Uniform & operator=(glm::vec4 const & data);
        Uniform & operator=(glm::mat3 const & data);
        Uniform & operator=(glm::mat4 const & data);

        void set_data(bool data);
        void set_data(int data);
        void set_data(float data);
        void set_data(std::vector<float> const & data);
        void set_data(glm::vec2 const & data);
        void set_data(glm::vec3 const & data);
        void set_data(glm::vec4 const & data);
        void set_data(glm::mat3 const & data);
        void set_data(glm::mat4 const & data);
    private:
        bool need_new_storage(UniformType type, size_t count);

        UniformType type;
        std::shared_ptr<void> shadowed_data;
        size_t count;
        size_t bytes;
    };
}

#endif
