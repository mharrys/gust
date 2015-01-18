#include "pass.hpp"

#include "program.hpp"

gst::Pass::Pass()
    : Pass(nullptr)
{
}

gst::Pass::Pass(std::shared_ptr<Program> program)
    : blend_mode(BlendMode::NONE),
      cull_face(CullFace::NONE),
      depth_mask(true),
      depth_test(false),
      program(program)
{
}

void gst::Pass::apply(MatrixState &, LightNodes &)
{
}
