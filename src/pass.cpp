#include "pass.hpp"

gst::Pass::Pass(Viewport viewport, std::shared_ptr<Program> program)
    : blend_mode(BlendMode::NONE),
      cull_face(CullFace::NONE),
      depth_mask(true),
      depth_test(false),
      viewport(viewport),
      program(program)
{
}
