#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

#include <memory>

namespace gst
{
    class Framebuffer;
    class Logger;
    class RenderState;
    class RenderTarget;
    class Scene;

    class Renderer {
    public:
        Renderer() = default;
        Renderer(
            std::shared_ptr<Logger> logger,
            std::shared_ptr<RenderState> render_state);

        void clear(bool color = true, bool depth = true);
        void render(Scene & scene);
        void render(Scene & scene, RenderTarget & target);
        void check_errors();

        bool auto_clear;
        bool auto_clear_color;
        bool auto_clear_depth;
    private:
        std::shared_ptr<Logger> logger;
        std::shared_ptr<RenderState> render_state;
    };
}

#endif
