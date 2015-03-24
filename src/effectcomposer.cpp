#include "effectcomposer.hpp"

#include "effectcomposerfactory.hpp"
#include "framebuffer.hpp"
#include "framebufferattachment.hpp"
#include "renderbuffer.hpp"
#include "resolution.hpp"
#include "pass.hpp"
#include "shadoweddata.hpp"
#include "texture2d.hpp"
#include "viewport.hpp"

gst::EffectComposer gst::EffectComposer::create(std::shared_ptr<Logger> logger)
{
    gst::EffectComposerFactory factory(logger);
    return factory.create();
}

void gst::EffectComposer::render(Scene & scene, Resolution size)
{
    resize(size);
    renderer.render(scene, targets[write]);
    renderer.check_errors();
    swap();
}

void gst::EffectComposer::render_pass(Effect & effect)
{
    const auto temp = effect.get_samplers()[0];
    const auto viewport = effect.get_pass().viewport;

    set_resolution(effect, viewport);
    set_read(effect);

    resize(viewport);
    renderer.render(quad, effect, targets[write]);
    renderer.check_errors();
    swap();

    effect.get_samplers()[0] = temp;
}

void gst::EffectComposer::render_to_screen(Resolution size)
{
    set_resolution(copy, size);
    set_read(copy);

    renderer.render(quad, copy);
    renderer.check_errors();
}

void gst::EffectComposer::render_to_texture(std::shared_ptr<Texture2D> texture)
{
    const auto temp = targets[write]->get_color_attachment();
    targets[write]->set_color({ texture });

    set_resolution(copy, texture->get_size());
    set_read(copy);

    renderer.render(quad, copy, targets[write]);
    renderer.check_errors();

    targets[write]->set_color(temp);
}

gst::EffectComposer::EffectComposer(
    Renderer renderer,
    RenderTargets targets,
    Effect copy,
    Scene quad)
    : renderer(renderer),
      targets(targets),
      read(0),
      write(1),
      copy(copy),
      quad(quad)
{
}

void gst::EffectComposer::resize(Resolution size)
{
    const auto color_attachment = targets[write]->get_color_attachment();
    auto texture = std::static_pointer_cast<Texture2D>(color_attachment.get_resource());
    texture->set_size(size);

    const auto depth_attachment = targets[write]->get_depth_attachment();
    auto renderbuffer = std::static_pointer_cast<Renderbuffer>(depth_attachment.get_resource());
    renderbuffer->set_size(size);
}

void gst::EffectComposer::swap()
{
    read++;
    write++;
}

void gst::EffectComposer::set_resolution(Effect & effect, Resolution size)
{
    copy.get_pass().viewport = { size };
    effect["resolution"] = glm::vec2(size.get_width(), size.get_height());
}

void gst::EffectComposer::set_read(Effect & effect)
{
    const auto unit = 0;
    const auto attachment = targets[read]->get_color_attachment();
    effect.bind_sampler("read", std::static_pointer_cast<Texture>(attachment.get_resource()), unit);
}
