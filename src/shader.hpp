#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

#include "graphicsdevice.hpp"

namespace gst
{
    // The responsibility of this class is to mirror a shader object on the
    // graphics card.
    class Shader {
    public:
        // Return shader type.
        virtual ShaderType get_type() const = 0;
        // Return identifier on the graphics card.
        virtual ShaderHandle get_handle() const = 0;
    };
}

#endif
