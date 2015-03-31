#include "shadedpass.hpp"

#include "annotationfree.hpp"
#include "annotationarray.hpp"
#include "light.hpp"
#include "program.hpp"
#include "shadoweddata.hpp"
#include "uniformmapimpl.hpp"

gst::ShadedPass::ShadedPass(std::shared_ptr<Program> program)
    : Pass(program),
      uniforms(std::make_shared<UniformMapImpl>(std::unique_ptr<AnnotationFormatter>(new AnnotationFree()))),
      model_view("model_view"),
      projection("projection"),
      normal("nm"),
      eye_position("eye_position"),
      light_enabled("enabled"),
      light_position("position")
{
}

void gst::ShadedPass::apply(ModelState & model_state)
{
    uniforms->get_uniform(model_view) = model_state.model_view;
    uniforms->get_uniform(projection) = model_state.projection;
    uniforms->get_uniform(normal) = model_state.normal;
    uniforms->get_uniform(eye_position) = model_state.eye_position;
    program->merge_uniforms(*uniforms);

    for (auto light_node : model_state.light_nodes) {
        auto & light = light_node.get_light();
        light.get_uniform(light_enabled) = light.get_enabled();
        light.get_uniform(light_position) = model_state.view * glm::vec4(light_node.position, 1.0f);
        program->merge_uniforms(light.get_uniforms());
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

void gst::ShadedPass::set_eye_position_annotation(std::string const & eye_position)
{
    this->eye_position = eye_position;
}

void gst::ShadedPass::set_light_enabled_annotation(std::string const & light_enabled)
{
    this->light_enabled = light_enabled;
}

void gst::ShadedPass::set_light_position_annotation(std::string const & light_position)
{
    this->light_position = light_position;
}
