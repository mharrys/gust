#include "model.hpp"

gst::Model::Model(Mesh mesh, Material material)
    : mesh(mesh),
      material(material)
{
}

gst::Mesh & gst::Model::get_mesh()
{
    return mesh;
}

gst::Material & gst::Model::get_material()
{
    return material;
}
