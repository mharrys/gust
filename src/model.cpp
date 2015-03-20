#include "model.hpp"

gst::Model::Model(Mesh mesh, Effect effect)
    : mesh(mesh),
      effect(effect)
{
}

gst::Mesh & gst::Model::get_mesh()
{
    return mesh;
}

gst::Effect & gst::Model::get_effect()
{
    return effect;
}
