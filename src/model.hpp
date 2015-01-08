#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "mesh.hpp"
#include "surface.hpp"

namespace gst
{
    class Model {
    public:
        Model(Mesh mesh, Surface surface);

        Mesh mesh;
        Surface surface;
    };
}

#endif
