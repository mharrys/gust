#include "renderer.hpp"

#include "graphicsdevice.hpp"
#include "framebuffer.hpp"
#include "lightnodecollector.hpp"
#include "logger.hpp"
#include "noderenderer.hpp"
#include "renderstate.hpp"
#include "scene.hpp"

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

    LightNodeCollector collector;
    scene.traverse(collector);

    NodeRenderer renderer(render_state, scene.get_eye(), std::move(collector.get_lights()));
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
