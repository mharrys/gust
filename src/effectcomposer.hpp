#ifndef EFFECTCOMPOSER_HPP_INCLUDED
#define EFFECTCOMPOSER_HPP_INCLUDED

#include "filter.hpp"
#include "renderbuffer.hpp"
#include "renderer.hpp"
#include "resolution.hpp"
#include "scene.hpp"
#include "texture.hpp"

#include <array>
#include <memory>

namespace gst
{
    class EffectComposerFactory;
    class Framebuffer;
    class Texture2D;

    typedef std::array<std::shared_ptr<Framebuffer>, 2> RenderTargets;

    // The responsibility of this class is to setup and run a post-processing
    // pipeline to achieve a effect.
    class EffectComposer {
    public:
        // Construct effect composer with default implementations with a copy
        // filter and a fullscreen quad scene with orthographic projection.
        static EffectComposer create(std::shared_ptr<Logger> logger);
        // Construct empty effect composer.
        EffectComposer() = default;
        // Construct effect composer from specified implementations.
        EffectComposer(
            Renderer renderer,
            RenderTargets targets,
            Filter copy,
            Scene screen);
        // Render scene into framebuffer.
        void render(Scene & scene);
        // Render scene using specified filter into framebuffer.
        void render(Scene & scene, Filter & filter);
        // Setup and run post-process filter. This will override texture unit
        // 0 during render.
        void render_filter(Filter & filter);
        // Setup and run post-process filter. This will use specified texture
        // as read on texture unit 0 during render.
        void render_filter(Filter & filter, std::shared_ptr<Texture2D> texture);
        // Copy current processing state to specified texture. It is expected
        // that the specified texture is of the same size as the renderer.
        void render_to_texture(std::shared_ptr<Texture2D> texture);
        // Copy read to screen.
        void render_to_screen();
        // Copy texture to screen.
        void render_to_screen(std::shared_ptr<Texture2D> texture);
        // Set size of render. This will resize both the read and write
        // framebuffers which will in effect invalidate any previous
        // processing.
        void set_size(Resolution size);
        // Set format on color attachments.
        void set_color_format(TextureFormat format);
        // Set format on depth attachments.
        void set_depth_format(RenderbufferFormat format);
        // Set resolution annotation.
        void set_resolution_annotation(std::string const & resolution_annotation);
        // Set read annotation.
        void set_read_annotation(std::string const & read_annotation);
    private:
        void swap();
        void set_resolution(Filter & filter, Resolution size);
        void set_read(Filter & filter);
        void set_read(Filter & filter, std::shared_ptr<Texture2D> texture);

        Renderer renderer;
        Resolution size;

        RenderTargets targets;
        unsigned read:1, write:1;

        Filter copy;
        Scene screen;

        std::string resolution_annotation;
        std::string read_annotation;
    };
}

#endif
