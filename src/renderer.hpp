#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

#include "glm.hpp"

#include <memory>

namespace gst
{
    class Framebuffer;
    class GraphicsDevice;
    class LightNode;
    class Logger;
    class Material;
    class RenderState;
    class Scene;
    class Viewport;

    // The responsibility of this class is to prepare a scene for rendering.
    class Renderer {
    public:
        // Construct renderer with default implementation of graphics device
        // and render state and specified logger.
        static Renderer create(std::shared_ptr<Logger> logger);
        // Construct renderer with specified implementations of graphics
        // device, render state and logger.
        Renderer(
            std::shared_ptr<GraphicsDevice> device,
            std::shared_ptr<RenderState> render_state,
            std::shared_ptr<Logger> logger);
        // Clear specified buffers.
        void clear(bool color, bool depth);
        // Render scene.
        void render(Scene & scene);
        // Render scene using specified material.
        void render(Scene & scene, Material & material);
        // Render scene into framebuffer.
        void render(Scene & scene, std::shared_ptr<Framebuffer> target);
        // Render scene into framebuffer using specified material.
        void render(Scene & scene, Material & material, std::shared_ptr<Framebuffer> target);
        // Set auto clear flag on specified buffers.
        void set_auto_clear(bool auto_clear_color, bool auto_clear_depth);
        // Set auto check errors.
        void set_auto_check_errors(bool auto_check_render, bool auto_check_framebuffer);
        // Set viewport.
        void set_viewport(Viewport viewport);
    private:
        void render(Scene & scene, Material * const material, std::shared_ptr<Framebuffer> target);

        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<RenderState> render_state;
        std::shared_ptr<Logger> logger;

        bool auto_clear_color;
        bool auto_clear_depth;
        bool auto_check_render;
        bool auto_check_framebuffer;
    };
}

#endif
