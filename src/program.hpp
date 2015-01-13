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
    class ProgramImpl;
    class RenderState;
    class Shader;

    typedef std::pair<int, std::string> AttribLocation;
    typedef std::unordered_map<std::string, int> UniformCache;

    class Program {
        friend RenderState;
    public:
        Program() = default;
        Program(
            std::shared_ptr<RenderState> render_state,
            std::shared_ptr<Logger> logger,
            std::vector<Shader> shaders = {},
            std::vector<AttribLocation> const & locations = {});

        bool operator==(Program const & other);
        bool operator!=(Program const & other);
        explicit operator bool() const;

        void uniform(std::string const & name, bool value);
        void uniform(std::string const & name, int value);
        void uniform(std::string const & name, float value);
        void uniform(std::string const & name, glm::mat3 const & value);
        void uniform(std::string const & name, glm::mat4 const & value);
        void uniform(std::string const & name, glm::vec2 const & value);
        void uniform(std::string const & name, glm::vec3 const & value);
        void uniform(std::string const & name, glm::vec4 const & value);
        void uniform(std::string const & name, std::vector<float> const & value);
    private:
        int uniform(std::string const & name);

        void push();
        void pop();

        std::shared_ptr<ProgramImpl> impl;
        std::shared_ptr<RenderState> render_state;
        std::shared_ptr<Logger> logger;
        UniformCache uniforms;
    };
}

#endif
