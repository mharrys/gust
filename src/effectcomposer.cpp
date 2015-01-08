#include "effectcomposer.hpp"

#include "effect.hpp"
#include "effectnode.hpp"
#include "material.hpp"
#include "pass.hpp"
#include "program.hpp"
#include "texture.hpp"

gst::EffectComposer::EffectComposer(
    Renderer & renderer,
    RenderTargets targets,
    std::shared_ptr<Effect> screen,
    Scene & scene)
    : renderer(renderer),
      targets(std::move(targets)),
      read(0),
      write(1),
      screen(screen),
      scene(std::move(scene))
{
}

void gst::EffectComposer::render(Scene & scene)
{
    renderer.render(scene, targets[write]);
    swap();
}

void gst::EffectComposer::render_to_screen()
{
    screen->read = targets[read];
    renderer.render(scene);
}

void gst::EffectComposer::pass(Pass & pass)
{
    screen->read = targets[read];
    screen->bind_callback = nullptr;

    pass.prepare(*screen.get());
    render(scene);

    screen->bind_callback = nullptr;
}

void gst::EffectComposer::swap()
{
    read++;
    write++;
}
