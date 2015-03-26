#include "shadedpass.hpp"

#include "annotationfree.hpp"
#include "annotationarray.hpp"
#include "program.hpp"
#include "shadoweddata.hpp"
#include "uniformmapimpl.hpp"

gst::ShadedPass::ShadedPass(std::shared_ptr<Program> program)
    : Pass(program),
      uniforms(std::make_shared<UniformMapImpl>(std::unique_ptr<AnnotationFormatter>(new AnnotationFree()))),
      model_view("model_view"),
      projection("projection"),
      normal("nm"),
      enabled("enabled"),
      position("position")
{
}

void gst::ShadedPass::apply(ModelState const & state)
{
    uniforms->get_uniform(model_view) = state.model_view;
    uniforms->get_uniform(projection) = state.projection;
    uniforms->get_uniform(normal) = state.normal;
    program->set_uniforms(*uniforms);

    for (auto i = 0u; i < state.light_nodes.size(); i++) {
        auto & light_node = state.light_nodes[i];
        auto & light = light_node.get_light();

        // special uniforms
        light.get_uniform(enabled) = light.get_enabled();
        light.get_uniform(position) = state.view * glm::vec4(light_node.position, 1.0f);

        // special case if annotation array
        auto & uniforms = light.get_uniforms();
        if (auto * formatter = dynamic_cast<AnnotationArray *>(&uniforms.get_formatter())) {
            formatter->set_current_index(i);
        }

        program->set_uniforms(uniforms);
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

void gst::ShadedPass::set_enabled_annotation(std::string const & enabled)
{
    this->enabled = enabled;
}

void gst::ShadedPass::set_position_annotation(std::string const & position)
{
    this->position = position;
}
