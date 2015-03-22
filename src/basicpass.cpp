#include "basicpass.hpp"

#include "annotationbasic.hpp"
#include "program.hpp"
#include "shadoweddata.hpp"
#include "uniformmapimpl.hpp"

gst::BasicPass::BasicPass(Viewport viewport, std::shared_ptr<Program> program)
    : Pass(viewport, program),
      uniforms(std::make_shared<UniformMapImpl>(std::make_shared<AnnotationBasic>())),
      model_view("model_view"),
      projection("projection")
{
}

void gst::BasicPass::apply(ModelState const & state)
{
    uniforms->get_uniform(model_view) = state.model_view;
    uniforms->get_uniform(projection) = state.projection;
    program->set_uniforms(*uniforms);
}

void gst::BasicPass::set_model_view_annotation(std::string const & model_view)
{
    this->model_view = model_view;
}

void gst::BasicPass::set_projection_annotation(std::string const & projection)
{
    this->projection = projection;
}
