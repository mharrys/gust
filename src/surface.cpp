#include "surface.hpp"

gst::Surface::Surface(Material & material, Program & program)
    : blend_mode(BlendMode::NONE),
      cull_face(CullFace::NONE),
      depth_mask(true),
      depth_test(false),
      opacity(1.0f),
      material(material),
      program(program)
{
}
