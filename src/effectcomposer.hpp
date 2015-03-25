#ifndef EFFECTCOMPOSER_HPP_INCLUDED
#define EFFECTCOMPOSER_HPP_INCLUDED

#include "effect.hpp"
#include "renderer.hpp"
#include "resolution.hpp"
#include "scene.hpp"

#include <array>
#include <memory>

namespace gst
{
    class EffectComposerFactory;
    class Framebuffer;
    class Texture2D;

    typedef std::array<std::shared_ptr<Framebuffer>, 2> RenderTargets;

    // The responsibility of this class is to setup and run a post-processing
    // pipeline.
    class EffectComposer {
        friend EffectComposerFactory;
    public:
        static EffectComposer create(std::shared_ptr<Logger> logger);
        // Render scene into read-texture.
        void render(Scene & scene);
        // Setup and run post-process effect on read-texture. This will
        // override texture unit 0 during render.
        void render_pass(Effect & effect);
        // Copy read-texture to specified texture, it is expected that the
        // specified texture is of the same size as the effect composer.
        void render_to_texture(std::shared_ptr<Texture2D> texture);
        // Copy read-texture to screen.
        void render_to_screen();
        // Set size of render.
        void set_size(Resolution size);
    private:
        EffectComposer(
            Renderer renderer,
            RenderTargets targets,
            Effect copy,
            Scene screen);
        void swap();
        void set_resolution(Effect & effect, Resolution size);
        void set_read(Effect & effect);

        Renderer renderer;
        Resolution size;

        RenderTargets targets;
        unsigned read:1, write:1;

        Effect copy;
        Scene screen;
    };
}

#endif
