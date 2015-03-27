#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "material.hpp"
#include "mesh.hpp"

namespace gst
{
    // The responsibility of this class is to describe a how a model in a
    // scene should be rendered.
    class Model {
    public:
        Model(Mesh mesh, Material material);
        // Return mesh.
        Mesh & get_mesh();
        // Return material.
        Material & get_material();
    private:
        Mesh mesh;
        Material material;
    };
}

#endif
