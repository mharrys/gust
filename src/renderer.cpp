#include "renderer.hpp"

#include "annotationarray.hpp"
#include "cameranode.hpp"
#include "graphicsdevice.hpp"
#include "framebuffer.hpp"
#include "light.hpp"
#include "lightnode.hpp"
#include "lightnodecollector.hpp"
#include "logger.hpp"
#include "noderenderer.hpp"
#include "renderstate.hpp"
#include "scene.hpp"
#include "shadoweddata.hpp"
#include "uniformmap.hpp"

gst::Renderer::Renderer(
    std::shared_ptr<GraphicsDevice> device,
    std::shared_ptr<RenderState> render_state,
    std::shared_ptr<Logger> logger)
    : device(device),
      render_state(render_state),
      logger(logger),
      auto_clear_color(true),
      auto_clear_depth(true)
{
}

void gst::Renderer::clear(bool color, bool depth)
{
    device->clear(color, depth);
}

void gst::Renderer::render(Scene & scene)
{
    if (auto_clear_color || auto_clear_depth) {
        clear(auto_clear_color, auto_clear_depth);
    }

    auto eye = scene.get_eye();

    LightNodeCollector collector;
    scene.traverse(collector);

    ModelState model_state;
    model_state.view = eye->get_view();
    model_state.projection = eye->get_projection();
    model_state.light_nodes = collector.get_light_nodes();
    prepare_lights(model_state.view, model_state.light_nodes);

    NodeRenderer renderer(render_state, std::move(model_state));
    scene.traverse(renderer);
}

void gst::Renderer::render(Scene & scene, std::shared_ptr<Framebuffer> target)
{
    render_state->set_framebuffer(target);
    for (auto status : device->check_framebuffer_status()) {
        logger->log(status);
    }
    render(scene);
    render_state->set_framebuffer(nullptr);
}

void gst::Renderer::check_errors()
{
    for (auto error : device->get_errors()) {
        logger->log(error);
    }
}

void gst::Renderer::set_auto_clear(bool auto_clear_color, bool auto_clear_depth)
{
    this->auto_clear_color = auto_clear_color;
    this->auto_clear_depth = auto_clear_depth;
}

void gst::Renderer::prepare_lights(glm::mat4 view, std::vector<LightNode> & lights) const
{
    for (unsigned int i = 0; i < lights.size(); i++) {
        auto light = lights[i].get_light();

        // special uniforms
        auto uniforms = light->get_uniforms();
        uniforms->get_uniform("enabled") = light->get_enabled();
        uniforms->get_uniform("position") = view * glm::vec4(lights[i].position, 1.0f);

        // special case if annotation array
        if (auto * formatter = dynamic_cast<AnnotationArray *>(&uniforms->get_formatter())) {
            formatter->set_current_index(i);
        }
    }
}
