#ifndef SHADERIMPL_HPP_INCLUDED
#define SHADERIMPL_HPP_INCLUDED

#include "translator.hpp"

#include <memory>
#include <string>

namespace gst
{
    class ProgramImpl;

    class ShaderImpl {
        friend ProgramImpl;
    public:
        ShaderImpl(ShaderType type);
        ~ShaderImpl();
        bool compile(std::string const & source);
        std::string get_error_log();
    private:
        GLuint id;
        GLenum type;
        std::string source;

        Translator translator;
    };
}

#endif
