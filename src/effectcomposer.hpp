#ifndef EFFECTCOMPOSER_HPP_INCLUDED
#define EFFECTCOMPOSER_HPP_INCLUDED

#include "renderer.hpp"
#include "rendertarget.hpp"
#include "scene.hpp"

#include <array>
#include <memory>

namespace gst
{
    class Effect;
    class Pass;
    class Scene;

    typedef std::array<RenderTarget, 2> RenderTargets;

    class EffectComposer { // based on ideas from https://github.com/spite/Wagner
    public:
        EffectComposer() = default;
        EffectComposer(
            Renderer & renderer,
            RenderTargets targets,
            std::shared_ptr<Effect> screen,
            Scene & scene);
        void render(Scene & scene);
        void render_to_screen();
        void pass(Pass & pass);
    private:
        void swap();

        Renderer renderer;
        RenderTargets targets;
        unsigned read:1, write:1;

        std::shared_ptr<Effect> screen;
        Scene scene;
    };
}

#endif
