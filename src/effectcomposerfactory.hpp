#ifndef EFFECTCOMPOSERFACTORY_HPP_INCLUDED
#define EFFECTCOMPOSERFACTORY_HPP_INCLUDED

#include "programpool.hpp"
#include "renderer.hpp"

#include <memory>

namespace gst
{
    class EffectComposer;
    class Logger;
    class Renderbuffer;
    class Resolution;
    class Texture;

    class EffectComposerFactory {
    public:
        EffectComposerFactory(
            std::shared_ptr<Logger> logger,
            ProgramPool & programs,
            Renderer & renderer);
        EffectComposer create(
            std::string const & vs_path,
            std::string const & fs_path,
            Resolution size);
    private:
        RenderTarget create_target(Resolution size);
        Texture create_texture(Resolution size);
        Renderbuffer create_renderbuffer(Resolution size);

        std::shared_ptr<Logger> logger;
        std::shared_ptr<RenderState> render_state;
        ProgramPool programs;
        Renderer renderer;
    };
}

#endif
