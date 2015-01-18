#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include "uniform.hpp"

#include <vector>

namespace gst
{
    class Light {
    public:
        std::vector<Uniform> uniforms;
    };
}

#endif
