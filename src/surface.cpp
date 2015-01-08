#include "surface.hpp"

gst::Surface::Surface(Material & material, Program & program)
    : cull_face(CullFace::NONE),
      depth_mask(true),
      depth_test(false),
      material(material),
      program(program)
{
}
