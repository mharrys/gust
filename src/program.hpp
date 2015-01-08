#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "glm.hpp"

#include <memory>
#include <string>
#include <vector>
#include <unordered_map>

namespace gst
{
    class Logger;
    class RenderState;
    class ProgramImpl;

    typedef int Uniform;
    typedef std::unordered_map<std::string, Uniform> UniformCache;

    // TODO: state handling with render state
    class Program {
        friend RenderState;
    public:
        Program() = default;
        Program(std::shared_ptr<ProgramImpl> impl, std::shared_ptr<Logger> logger);

        bool operator==(Program const & other);
        bool operator!=(Program const & other);
        explicit operator bool() const;

        Uniform uniform(std::string const & name);
        void uniform(Uniform location, bool value);
        void uniform(Uniform location, int value);
        void uniform(Uniform location, float value);
        void uniform(Uniform location, glm::mat3 const & value);
        void uniform(Uniform location, glm::mat4 const & value);
        void uniform(Uniform location, glm::vec2 const & value);
        void uniform(Uniform location, glm::vec3 const & value);
        void uniform(Uniform location, glm::vec4 const & value);
        void uniform(Uniform location, std::vector<float> const & value);
    private:
        std::shared_ptr<ProgramImpl> impl;
        std::shared_ptr<Logger> logger;
        UniformCache uniforms;
    };
}

#endif
