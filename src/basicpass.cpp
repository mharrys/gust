#include "basicpass.hpp"

#include "annotationfree.hpp"
#include "program.hpp"
#include "shadoweddata.hpp"
#include "uniformmapimpl.hpp"

gst::BasicPass::BasicPass(std::shared_ptr<Program> program)
    : Pass(program),
      uniforms(std::make_shared<UniformMapImpl>(std::unique_ptr<AnnotationFormatter>(new AnnotationFree()))),
      model_view("model_view"),
      projection("projection")
{
}

void gst::BasicPass::apply(ModelState & state)
{
    uniforms->get_uniform(model_view) = state.model_view;
    uniforms->get_uniform(projection) = state.projection;
    program->merge_uniforms(*uniforms);
}

void gst::BasicPass::set_model_view_annotation(std::string const & model_view)
{
    this->model_view = model_view;
}

void gst::BasicPass::set_projection_annotation(std::string const & projection)
{
    this->projection = projection;
}
