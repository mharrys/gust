#include "pass.hpp"

gst::Pass::Pass(std::shared_ptr<Program> program)
    : program(program),
      blend_mode(BlendMode::NONE),
      cull_face(CullFace::NONE),
      depth_mask(true),
      depth_test(false)
{
}

void gst::Pass::set_blend_mode(BlendMode blend_mode)
{
    this->blend_mode = blend_mode;
}

void gst::Pass::set_cull_face(CullFace cull_face)
{
    this->cull_face = cull_face;
}

void gst::Pass::set_depth_mask(bool depth_mask)
{
    this->depth_mask = depth_mask;
}

void gst::Pass::set_depth_test(bool depth_test)
{
    this->depth_test = depth_test;
}

gst::BlendMode gst::Pass::get_blend_mode() const
{
    return blend_mode;
}

gst::CullFace gst::Pass::get_cull_face() const
{
    return cull_face;
}

bool gst::Pass::get_depth_mask() const
{
    return depth_mask;
}

bool gst::Pass::get_depth_test() const
{
    return depth_test;
}
