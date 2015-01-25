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
    class UniformArrayElement;
    class UniformGroup;

    typedef std::pair<int, std::string> AttributeLocation;
    typedef std::unordered_map<std::string, int> UniformCache;

    class Program {
        friend RenderState;
    public:
        Program() = default;
        Program(
            std::shared_ptr<Logger> logger,
            std::vector<Shader> shaders = {},
            std::vector<AttributeLocation> const & locations = {});

        bool operator==(Program const & other);
        bool operator!=(Program const & other);
        explicit operator bool() const;

        void update(std::string const & name, Uniform const & uniform);
        void update(UniformArrayElement const & element);
        void update(UniformGroup const & group);
    private:
        int location(std::string const & name);

        std::shared_ptr<ProgramImpl> impl;
        std::shared_ptr<Logger> logger;
        UniformCache uniforms;
    };
}

#endif
