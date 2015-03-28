#include "renderer.hpp"

#include "annotationarray.hpp"
#include "cameranode.hpp"
#include "graphicsdeviceimpl.hpp"
#include "graphicssynchronizer.hpp"
#include "framebuffer.hpp"
#include "lightnodecollector.hpp"
#include "logger.hpp"
#include "noderenderer.hpp"
#include "renderstate.hpp"
#include "scene.hpp"
#include "shadoweddata.hpp"
#include "uniformmap.hpp"

gst::Renderer gst::Renderer::create(std::shared_ptr<Logger> logger)
{
    auto device = std::make_shared<GraphicsDeviceImpl>();
    auto synchronizer = std::make_shared<GraphicsSynchronizer>(device, logger);
    auto render_state = std::make_shared<RenderState>(device, synchronizer);
    return Renderer(device, render_state, logger);
}

gst::Renderer::Renderer(
    std::shared_ptr<GraphicsDevice> device,
    std::shared_ptr<RenderState> render_state,
    std::shared_ptr<Logger> logger)
    : device(device),
      render_state(render_state),
      logger(logger),
      auto_clear_color(true),
      auto_clear_depth(true),
      auto_check_render(true),
      auto_check_framebuffer(true)
{
}

void gst::Renderer::clear(bool color, bool depth)
{
    device->clear(color, depth);
}

void gst::Renderer::render(Scene & scene)
{
    render(scene, nullptr, nullptr);
}

void gst::Renderer::render(Scene & scene, Filter & filter)
{
    render(scene, &filter, nullptr);
}

void gst::Renderer::render(Scene & scene, std::shared_ptr<Framebuffer> target)
{
    render(scene, nullptr, target);
}

void gst::Renderer::render(Scene & scene, Filter & filter, std::shared_ptr<Framebuffer> target)
{
    render(scene, &filter, target);
}

void gst::Renderer::set_auto_clear(bool auto_clear_color, bool auto_clear_depth)
{
    this->auto_clear_color = auto_clear_color;
    this->auto_clear_depth = auto_clear_depth;
}

void gst::Renderer::set_auto_check_errors(bool auto_check_render, bool auto_check_framebuffer)
{
    this->auto_check_render= auto_check_render;
    this->auto_check_framebuffer = auto_check_framebuffer;
}

void gst::Renderer::set_viewport(Viewport viewport)
{
    render_state->set_viewport(viewport);
}

void gst::Renderer::render(Scene & scene, Filter * const filter, std::shared_ptr<Framebuffer> target)
{
    if (target) {
        render_state->set_framebuffer(target);
        if (auto_check_framebuffer) {
            for (auto status : device->check_framebuffer_status()) {
                logger->log(status);
            }
        }
    }

    if (auto_clear_color || auto_clear_depth) {
        clear(auto_clear_color, auto_clear_depth);
    }

    auto & eye = scene.get_eye();

    auto collector = LightNodeCollector();
    scene.traverse(collector);

    auto model_state = ModelState();
    model_state.view = eye.get_view();
    model_state.projection = eye.get_projection();
    model_state.light_nodes = collector.get_light_nodes();

    // special case if one or more lights are stored in a array
    for (auto i = 0u; i < model_state.light_nodes.size(); i++) {
        auto & light_node = model_state.light_nodes[i];
        auto & light = light_node.get_light();
        auto & uniforms = light.get_uniforms();
        if (auto * formatter = dynamic_cast<AnnotationArray *>(&uniforms.get_formatter())) {
            formatter->set_current_index(i);
        }
    }

    auto renderer = NodeRenderer(device, render_state, model_state, filter);
    scene.traverse(renderer);

    if (auto_check_render) {
        for (auto error : device->get_errors()) {
            logger->log(error);
        }
    }

    if (target) {
        render_state->set_framebuffer(nullptr);
    }
}
