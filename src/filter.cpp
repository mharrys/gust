#include "filter.hpp"

#include "pass.hpp"

gst::Filter::Filter(Material material, std::shared_ptr<Pass> pass)
    : material(material),
      pass(pass)
{
}

gst::ShadowedData & gst::Filter::get_uniform(std::string const & annotation)
{
    return material.get_uniform(annotation);
}

gst::Textures & gst::Filter::get_textures()
{
    return material.get_textures();
}

gst::Material & gst::Filter::get_material()
{
    return material;
}

gst::Pass & gst::Filter::get_pass()
{
    return *pass;
}
