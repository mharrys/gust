#ifndef MODEL_HPP_INCLUDED
#define MODEL_HPP_INCLUDED

#include "effect.hpp"
#include "mesh.hpp"

namespace gst
{
    class Model {
    public:
        Model(Mesh mesh, Effect effect);

        Mesh mesh;
        Effect effect;
    };
}

#endif
