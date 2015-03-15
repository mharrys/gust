#include "shadedpass.hpp"

#include "annotationbasic.hpp"
#include "program.hpp"
#include "shadoweddata.hpp"
#include "uniformmapimpl.hpp"

gst::ShadedPass::ShadedPass()
    : ShadedPass(std::make_shared<UniformMapImpl>(std::make_shared<AnnotationBasic>()))
{
}

gst::ShadedPass::ShadedPass(std::shared_ptr<UniformMap> uniforms)
    : uniforms(uniforms),
      model_view("model_view"),
      projection("projection"),
      normal("nm")
{
}

void gst::ShadedPass::apply(ModelState const & state)
{
    uniforms->get_uniform(model_view) = state.model_view;
    uniforms->get_uniform(projection) = state.projection;
    uniforms->get_uniform(normal) = state.normal;
    program->set_uniforms(*uniforms);

    for (auto & light_node : state.light_nodes) {
        auto light = light_node.get_light();
        program->set_uniforms(*light->get_uniforms());
    }
}

void gst::ShadedPass::set_model_view_annotation(std::string const & model_view)
{
    this->model_view = model_view;
}

void gst::ShadedPass::set_projection_annotation(std::string const & projection)
{
    this->projection = projection;
}

void gst::ShadedPass::set_normal_annotation(std::string const & normal)
{
    this->normal = normal;
}
