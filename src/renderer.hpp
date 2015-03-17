#ifndef RENDERER_HPP_INCLUDED
#define RENDERER_HPP_INCLUDED

#include "effect.hpp"

#include "glm.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Framebuffer;
    class GraphicsDevice;
    class LightNode;
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
        // Render scene into framebuffer.
        void render(Scene & scene, std::shared_ptr<Framebuffer> target);
        // Render scene into framebuffer but override all effects with
        // specified effect.
        void render(Scene & scene, Effect & effect, std::shared_ptr<Framebuffer> target);
        // Check graphical errors, it will print errors using the logger.
        void check_errors();
        // Set auto clear flag on specified buffers.
        void set_auto_clear(bool auto_clear_color, bool auto_clear_depth);
    private:
        void prepare_lights(glm::mat4 view, std::vector<LightNode> & lights) const;

        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<RenderState> render_state;
        std::shared_ptr<Logger> logger;

        bool auto_clear_color;
        bool auto_clear_depth;

        Effect effect_override;
        bool use_effect_override;
    };
}

#endif
