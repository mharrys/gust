#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "effect.hpp"
#include "mesh.hpp"

namespace gst
{
    // The responsibility of this class is to describe a how a model in a
    // scene should be rendered.
    class Model {
    public:
        Model(Mesh mesh, Effect effect);
        // Return mesh.
        Mesh & get_mesh();
        // Return effect.
        Effect & get_effect();
    private:
        Mesh mesh;
        Effect effect;
    };
}

#endif
