#include "effectcomposer.hpp"

#include "effectcomposerfactory.hpp"
#include "filter.hpp"
#include "framebuffer.hpp"
#include "framebufferattachment.hpp"
#include "renderbuffer.hpp"
#include "resolution.hpp"
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
    Filter copy,
    Scene screen)
    : renderer(renderer),
      targets(targets),
      read(0),
      write(1),
      copy(copy),
      screen(screen),
      resolution_annotation("resolution"),
      read_annotation("read")
{
}

void gst::EffectComposer::render(Scene & scene)
{
    renderer.render(scene, targets[write]);
    swap();
}

void gst::EffectComposer::render(Scene & scene, Filter & filter)
{
    renderer.render(scene, filter, targets[write]);
    swap();
}

void gst::EffectComposer::render_filter(Filter & filter)
{
    const auto temp = filter.get_textures()[0];

    set_resolution(filter, size);
    set_read(filter);

    renderer.render(screen, filter, targets[write]);
    swap();

    filter.get_textures()[0] = temp;
}

void gst::EffectComposer::render_filter(Filter & filter, std::shared_ptr<Texture2D> texture)
{
    const auto temp = filter.get_textures()[0];

    set_resolution(filter, size);
    set_read(filter, texture);

    renderer.render(screen, filter, targets[write]);
    swap();

    filter.get_textures()[0] = temp;
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

void gst::EffectComposer::render_to_screen(std::shared_ptr<Texture2D> texture)
{
    set_resolution(copy, size);
    set_read(copy, texture);

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

void gst::EffectComposer::set_color_format(TextureFormat format)
{
    for (auto target : targets ) {
        const auto color_attachment = target->get_color_attachment();
        auto texture = std::static_pointer_cast<Texture2D>(color_attachment.get_resource());
        texture->set_internal_format(format);
    }
}

void gst::EffectComposer::set_depth_format(RenderbufferFormat format)
{
    for (auto target : targets ) {
        const auto depth_attachment = target->get_depth_attachment();
        auto renderbuffer = std::static_pointer_cast<Renderbuffer>(depth_attachment.get_resource());
        renderbuffer->set_format(format);
    }
}

void gst::EffectComposer::set_resolution_annotation(std::string const & resolution_annotation)
{
    this->resolution_annotation = resolution_annotation;
}

void gst::EffectComposer::set_read_annotation(std::string const & read_annotation)
{
    this->read_annotation = read_annotation;
}

void gst::EffectComposer::swap()
{
    read++;
    write++;
}

void gst::EffectComposer::set_resolution(Filter & filter, Resolution size)
{
    filter.get_uniform(resolution_annotation) = glm::vec2(size.get_width(), size.get_height());
}

void gst::EffectComposer::set_read(Filter & filter)
{
    const auto unit = 0;
    const auto attachment = targets[read]->get_color_attachment();
    filter.get_textures()[unit] = std::static_pointer_cast<Texture>(attachment.get_resource());
    filter.get_uniform(read_annotation) = unit;
}

void gst::EffectComposer::set_read(Filter & filter, std::shared_ptr<Texture2D> texture)
{
    const auto unit = 0;
    filter.get_textures()[unit] = texture;
    filter.get_uniform(read_annotation) = unit;
}
