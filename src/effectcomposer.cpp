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

void gst::EffectComposer::render(Scene & scene)
{
    renderer.render(scene, targets[write]);
    swap();
}

void gst::EffectComposer::render_pass(Effect & effect)
{
    const auto temp = effect.get_textures()[0];

    set_resolution(effect, size);
    set_read(effect);

    renderer.render(screen, effect, targets[write]);
    swap();

    effect.get_textures()[0] = temp;
}

void gst::EffectComposer::render_to_texture(std::shared_ptr<Texture2D> texture)
{
    const auto temp = targets[write]->get_color_attachment();
    targets[write]->set_color({ texture });

    set_resolution(copy, texture->get_size());
    set_read(copy);

    renderer.render(screen, copy, targets[write]);

    targets[write]->set_color(temp);
}

void gst::EffectComposer::render_to_screen()
{
    set_resolution(copy, size);
    set_read(copy);

    renderer.render(screen, copy);
}

void gst::EffectComposer::set_size(Resolution size)
{
    if (this->size == size) {
        return;
    }

    this->size = size;

    for (auto target : targets) {
        const auto color_attachment = target->get_color_attachment();
        auto texture = std::static_pointer_cast<Texture2D>(color_attachment.get_resource());
        texture->set_size(size);

        const auto depth_attachment = target->get_depth_attachment();
        auto renderbuffer = std::static_pointer_cast<Renderbuffer>(depth_attachment.get_resource());
        renderbuffer->set_size(size);
    }

    renderer.set_viewport(size);
}

gst::EffectComposer::EffectComposer(
    Renderer renderer,
    RenderTargets targets,
    Effect copy,
    Scene screen)
    : renderer(renderer),
      targets(targets),
      read(0),
      write(1),
      copy(copy),
      screen(screen)
{
}

void gst::EffectComposer::swap()
{
    read++;
    write++;
}

void gst::EffectComposer::set_resolution(Effect & effect, Resolution size)
{
    effect.get_uniform("resolution") = glm::vec2(size.get_width(), size.get_height());
}

void gst::EffectComposer::set_read(Effect & effect)
{
    const auto unit = 0;
    const auto attachment = targets[read]->get_color_attachment();
    effect.get_textures()[unit] = std::static_pointer_cast<Texture>(attachment.get_resource());
    effect.get_uniform("read") = unit;
}
