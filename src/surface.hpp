#ifndef SURFACE_HPP_INCLUDED
#define SURFACE_HPP_INCLUDED

#include "cullface.hpp"
#include "material.hpp"
#include "program.hpp"
#include "texture.hpp"

#include <memory>

namespace gst
{
    class Surface {
    public:
        Surface(Material & material, Program & program);

        CullFace cull_face;
        bool depth_mask;
        bool depth_test;

        Texture color_map;
        Texture normal_map;

        Material material;
        Program program;
    };
}

#endif
