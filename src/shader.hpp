#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include "graphicsresource.hpp"
#include "shadertype.hpp"

#include <string>

namespace gst
{
    // The responsibility of this class is to mirror a shader object on the
    // graphics card.
    class Shader : public GraphicsResource {
    public:
        virtual ~Shader() = default;
        // Return shader type.
        virtual ShaderType get_type() const = 0;
        // Return shader source.
        virtual std::string get_source() const = 0;
    };
}

#endif
