#include "basicpass.hpp"

#include "annotationbasic.hpp"
#include "program.hpp"
#include "shadoweddata.hpp"
#include "uniformmap.hpp"

gst::BasicPass::BasicPass()
    : BasicPass(std::make_shared<gst::UniformMap>(std::make_shared<gst::AnnotationBasic>()))
{
}

gst::BasicPass::BasicPass(std::shared_ptr<UniformCollection> uniforms)
    : uniforms(uniforms),
      model_view("model_view"),
      projection("projection")
{
}

void gst::BasicPass::apply(gst::MatrixState & matrices, gst::LightNodes &)
{
    uniforms->get_uniform(model_view) = matrices.model_view;
    uniforms->get_uniform(projection) = matrices.projection;
    program->set_uniforms(uniforms);
}

void gst::BasicPass::set_model_view_annotation(std::string const & model_view)
{
    this->model_view = model_view;
}

void gst::BasicPass::set_projection_annotation(std::string const & projection)
{
    this->projection = projection;
}