#ifndef EFFECTCOMPOSERFACTORY_HPP_INCLUDED
#define EFFECTCOMPOSERFACTORY_HPP_INCLUDED

#include "effectcomposer.hpp"

namespace gst
{
    class Logger;
    class Mesh;
    class Program;

    // The responsibility of this class is to build a effect composer.
    class EffectComposerFactory {
    public:
        EffectComposerFactory(std::shared_ptr<Logger> logger);
        // Return built effect composer.
        EffectComposer create();
    private:
        Material create_copy_filter();
        std::shared_ptr<Program> create_copy_program();
        RenderTargets create_render_targets();

        std::shared_ptr<Logger> logger;
    };
}

#endif
