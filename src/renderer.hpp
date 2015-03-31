#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

#include "glm.hpp"

#include <memory>

namespace gst
{
    class Filter;
    class Framebuffer;
    class GraphicsDevice;
    class LightNode;
    class Logger;
    class RenderState;
    class Scene;
    class Viewport;

    // The responsibility of this class is to prepare a scene for rendering.
    class Renderer {
    public:
        // Construct renderer with default implementations and specified
        // logger.
        static Renderer create(std::shared_ptr<Logger> logger);
        // Construct empty renderer.
        Renderer() = default;
        // Construct renderer from specified implementations.
        Renderer(
            std::shared_ptr<GraphicsDevice> device,
            std::shared_ptr<RenderState> render_state,
            std::shared_ptr<Logger> logger);
        // Clear specified buffers.
        void clear(bool color, bool depth);
        // Render scene.
        void render(Scene & scene);
        // Render scene using specified filter.
        void render(Scene & scene, Filter & filter);
        // Render scene into framebuffer.
        void render(Scene & scene, std::shared_ptr<Framebuffer> target);
        // Render scene into framebuffer using specified filter.
        void render(Scene & scene, Filter & filter, std::shared_ptr<Framebuffer> target);
        // Set auto clear flag on specified buffers.
        void set_auto_clear(bool auto_clear_color, bool auto_clear_depth);
        // Set check errors. If error occurs, the error checks are set to
        // false (to avoid flooding the logger with errors).
        void set_check_errors(bool check_render_error, bool check_framebuffer_error);
        // Set viewport.
        void set_viewport(Viewport viewport);
    private:
        void render(Scene & scene, Filter * const filter, std::shared_ptr<Framebuffer> target);

        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<RenderState> render_state;
        std::shared_ptr<Logger> logger;

        bool auto_clear_color;
        bool auto_clear_depth;
        bool check_render_error;
        bool check_framebuffer_error;
    };
}

#endif
