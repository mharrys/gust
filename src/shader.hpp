#ifndef SHADER_HPP_INCLUDED
#define SHADER_HPP_INCLUDED

namespace gst
{
    // Supported shader types.
    enum class ShaderType {
        VERTEX,
        FRAGMENT
    };

    // The responsibility of this class is to mirror a shader object on the
    // graphics card.
    class Shader {
    public:
        // Return shader type.
        virtual ShaderType get_type() const = 0;
    };
}

#endif
