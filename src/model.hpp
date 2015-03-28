#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "material.hpp"
#include "mesh.hpp"

namespace gst
{
    class Pass;

    // The responsibility of this class is to describe a model.
    class Model {
    public:
        Model(Mesh mesh, Material material, std::shared_ptr<Pass> pass);
        // Return mesh.
        Mesh & get_mesh();
        // Return material.
        Material & get_material();
        // Return pass.
        Pass & get_pass();
    private:
        Mesh mesh;
        Material material;
        std::shared_ptr<Pass> pass;
    };
}

#endif
