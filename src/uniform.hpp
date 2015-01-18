#ifndef UNIFORM_HPP_INCLUDED
#define UNIFORM_HPP_INCLUDED

#include "glm.hpp"

#include <array>
#include <cstring>
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
        Uniform(std::string name);
        Uniform(std::string name, bool value);
        Uniform(std::string name, int value);
        Uniform(std::string name, float value);
        Uniform(std::string name, std::vector<float> const & value);
        Uniform(std::string name, glm::vec2 const & value);
        Uniform(std::string name, glm::vec3 const & value);
        Uniform(std::string name, glm::vec4 const & value);
        Uniform(std::string name, glm::mat3 const & value);
        Uniform(std::string name, glm::mat4 const & value);

        bool operator==(Uniform const & other);
        bool operator!=(Uniform const & other);

        Uniform & operator=(bool value);
        Uniform & operator=(int value);
        Uniform & operator=(float value);
        Uniform & operator=(std::vector<float> const & value);
        Uniform & operator=(glm::vec2 const & value);
        Uniform & operator=(glm::vec3 const & value);
        Uniform & operator=(glm::vec4 const & value);
        Uniform & operator=(glm::mat3 const & value);
        Uniform & operator=(glm::mat4 const & value);

        void set_data(bool value);
        void set_data(int value);
        void set_data(float value);
        void set_data(std::vector<float> const & value);
        void set_data(glm::vec2 const & value);
        void set_data(glm::vec3 const & value);
        void set_data(glm::vec4 const & value);
        void set_data(glm::mat3 const & value);
        void set_data(glm::mat4 const & value);

        void set_name(std::string name);
        void set_array_name(std::string array_name);
        void set_array_index(unsigned int array_index);

        std::string get_name() const;
        std::string get_array_name() const;
    private:
        bool need_new_storage(UniformType type, size_t count);

        std::string name;
        std::string array_name;
        unsigned int array_index;

        UniformType type;
        std::shared_ptr<void> shadowed_data;
        size_t count;
        size_t bytes;
    };
}

#endif
