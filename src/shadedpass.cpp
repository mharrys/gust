#include "shadedpass.hpp"

#include "annotationbasic.hpp"
#include "program.hpp"
#include "shadoweddata.hpp"
#include "uniformmap.hpp"

gst::ShadedPass::ShadedPass()
    : ShadedPass(std::make_shared<gst::UniformMap>(std::make_shared<gst::AnnotationBasic>()))
{
}

gst::ShadedPass::ShadedPass(std::shared_ptr<gst::UniformCollection> uniforms)
    : uniforms(uniforms),
      model_view("model_view"),
      projection("projection"),
      normal("nm")
{
}

void gst::ShadedPass::apply(gst::MatrixState & matrices, gst::LightNodes & light_nodes)
{
    uniforms->get_uniform(model_view) = matrices.model_view;
    uniforms->get_uniform(projection) = matrices.projection;
    uniforms->get_uniform(normal) = matrices.normal;
    program->set_uniforms(uniforms);

    for (auto & light_node : light_nodes) {
        auto light = light_node.get_light();
        program->set_uniforms(light->get_uniforms());
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
