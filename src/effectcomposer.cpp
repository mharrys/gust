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

gst::EffectComposer::EffectComposer(
    Renderer renderer,
    RenderTargets targets,
    Material copy_filter,
    Scene screen)
    : renderer(renderer),
      targets(targets),
      read(0),
      write(1),
      copy_filter(copy_filter),
      screen(screen)
{
}

void gst::EffectComposer::render(Scene & scene)
{
    renderer.render(scene, targets[write]);
    swap();
}

void gst::EffectComposer::render_filter(Material & filter)
{
    const auto temp = filter.get_textures()[0];

    set_resolution(filter, size);
    set_read(filter);

    renderer.render(screen, filter, targets[write]);
    swap();

    filter.get_textures()[0] = temp;
}

void gst::EffectComposer::render_to_texture(std::shared_ptr<Texture2D> texture)
{
    const auto temp = targets[write]->get_color_attachment();
    targets[write]->set_color({ texture });

    set_resolution(copy_filter, texture->get_size());
    set_read(copy_filter);

    renderer.render(screen, copy_filter, targets[write]);

    targets[write]->set_color(temp);
}

void gst::EffectComposer::render_to_screen()
{
    set_resolution(copy_filter, size);
    set_read(copy_filter);

    renderer.render(screen, copy_filter);
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

void gst::EffectComposer::swap()
{
    read++;
    write++;
}

void gst::EffectComposer::set_resolution(Material & filter, Resolution size)
{
    filter.get_uniform("resolution") = glm::vec2(size.get_width(), size.get_height());
}

void gst::EffectComposer::set_read(Material & filter)
{
    const auto unit = 0;
    const auto attachment = targets[read]->get_color_attachment();
    filter.get_textures()[unit] = std::static_pointer_cast<Texture>(attachment.get_resource());
    filter.get_uniform("read") = unit;
}
