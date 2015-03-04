#ifndef SHADERIMPL_HPP_INCLUDED
#define SHADERIMPL_HPP_INCLUDED

#include "shader.hpp"

namespace gst
{
    class ShaderImpl : public Shader {
    public:
        ShaderImpl(ShaderType type, std::string source);
        ShaderType get_type() const;
        std::string get_source() const;
    private:
        ShaderType type;
        std::string source;
    };
}

#endif
