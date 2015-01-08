#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include <memory>

namespace gst
{
    class ProgramFactory;
    class ShaderImpl;

    enum class ShaderType {
        VERTEX,
        FRAGMENT
    };

    class Shader {
        friend ProgramFactory;
    public:
        Shader() = default;
        Shader(ShaderType type, std::string const & source);

        bool operator==(Shader const & other);
        bool operator!=(Shader const & other);
        explicit operator bool() const;

        std::string get_compile_error() const;
    private:
        std::shared_ptr<ShaderImpl> impl;
        bool compile_successful;
        std::string error;
    };
}

#endif
