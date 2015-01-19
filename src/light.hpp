#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include "uniformarrayelement.hpp"

#include <vector>

namespace gst
{
    class Light {
    public:
        Light(std::string const & array_name);
        Light(UniformArrayElement const & uniforms);

        UniformArrayElement uniforms;
    };
}

#endif
