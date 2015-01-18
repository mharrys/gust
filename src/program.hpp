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
    class Uniform;

    typedef std::pair<int, std::string> AttribLocation;
    typedef std::unordered_map<std::string, int> UniformCache;

    class Program {
        friend RenderState;
    public:
        Program() = default;
        Program(
            std::shared_ptr<Logger> logger,
            std::vector<Shader> shaders = {},
            std::vector<AttribLocation> const & locations = {});

        bool operator==(Program const & other);
        bool operator!=(Program const & other);
        explicit operator bool() const;

        void update(Uniform const & uniform);
        void update(std::vector<Uniform> const & uniforms);
    private:
        int location(std::string const & name);

        std::shared_ptr<ProgramImpl> impl;
        std::shared_ptr<Logger> logger;
        UniformCache uniforms;
    };
}

#endif
