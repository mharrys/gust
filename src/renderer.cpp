#include "renderer.hpp"

#include "cameranode.hpp"
#include "groupnode.hpp"
#include "framebuffer.hpp"
#include "lightnodecollector.hpp"
#include "logger.hpp"
#include "noderenderer.hpp"
#include "renderstate.hpp"
#include "rendertarget.hpp"
#include "scene.hpp"

gst::Renderer::Renderer(
    std::shared_ptr<Logger> logger,
    std::shared_ptr<RenderState> render_state)
    : auto_clear(true),
      auto_clear_color(true),
      auto_clear_depth(true),
      logger(logger),
      render_state(render_state)
{
}

void gst::Renderer::clear(bool color, bool depth)
{
    render_state->clear_buffers(color, depth);
}

void gst::Renderer::render(Scene & scene)
{
    if (auto_clear) {
        clear(auto_clear_color, auto_clear_depth);
    }

    LightNodeCollector collector;
    scene.traverse(collector);

    NodeRenderer renderer(render_state, scene.eye, std::move(collector.lights));
    scene.traverse(renderer);
}

void gst::Renderer::render(Scene & scene, RenderTarget & target)
{
    render_state->push();
    render_state->set_framebuffer(target.framebuffer);
    render_state->set_viewport(target.get_size());
    for (auto status : target.framebuffer.get_status()) {
        logger->log(status);
    }
    render(scene);
    render_state->pop();
}

void gst::Renderer::check_errors()
{
    for (auto error : render_state->check_errors()) {
        logger->log(error);
    }
}
