#include "model.hpp"

#include "pass.hpp"

gst::Model::Model(Mesh mesh, Material material, std::shared_ptr<Pass> pass)
    : mesh(mesh),
      material(material),
      pass(pass)
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

gst::Pass & gst::Model::get_pass()
{
    return *pass;
}
