#ifndef SHADERIMPL_HPP_INCLUDED
#define SHADERIMPL_HPP_INCLUDED

#include "shader.hpp"

namespace gst
{
    class ShaderImpl : public Shader {
    public:
        // Construct copy vertex shader.
        static ShaderImpl create_copy_vs();
        // Construct copy fragment shader.
        static ShaderImpl create_copy_fs();

        // Construct shader from a shader type and shader source. The shader
        // type must describe the shader source.
        ShaderImpl(ShaderType type, std::string source);

        ShaderType get_type() const final;
        std::string get_source() const final;
    private:
        ShaderType type;
        std::string source;
    };
}

#endif
