#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

#include <memory>

namespace gst
{
    class Framebuffer;
    class GraphicsDevice;
    class Logger;
    class RenderState;
    class Scene;

    // The responsibility of this class is to prepare a scene for rendering.
    class Renderer {
    public:
        Renderer() = default;
        Renderer(
            std::shared_ptr<GraphicsDevice> device,
            std::shared_ptr<RenderState> render_state,
            std::shared_ptr<Logger> logger);
        // Clear specified buffers.
        void clear(bool color, bool depth);
        // Render scene.
        void render(Scene & scene);
        // Render scene into framebuffer. Once the framebuffer is set, the
        // renderer will check its status and print any messages to the
        // logger.
        void render(Scene & scene, std::shared_ptr<Framebuffer> target);
        // Check graphical errors, it will print errors using the logger.
        void check_errors();
        // Set auto clear flag on specified buffers.
        void set_auto_clear(bool auto_clear_color, bool auto_clear_depth);
    private:
        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<RenderState> render_state;
        std::shared_ptr<Logger> logger;

        bool auto_clear_color;
        bool auto_clear_depth;
    };
}

#endif
