#ifndef RENDERSTATE_HPP_INCLUDED
#define RENDERSTATE_HPP_INCLUDED

#include "blendmode.hpp"
#include "color.hpp"
#include "cullface.hpp"
#include "viewport.hpp"

#include <memory>
#include <unordered_map>
#include <vector>

namespace gst
{
    class Buffer;
    class Framebuffer;
    class GraphicsDevice;
    class GraphicsSynchronizer;
    class Program;
    class Renderbuffer;
    class Texture;
    class VertexArray;

    typedef std::unordered_map<int, std::shared_ptr<Texture>> TextureLookup;

    // The responsibility of this class is to cache all operations that
    // changes the state on the graphics card. It will reset to a sensible
    // default state when created so that all future operations will reflect
    // the current state on the graphics card.
    class RenderState {
    public:
        RenderState(
            std::shared_ptr<GraphicsDevice> device,
            std::shared_ptr<GraphicsSynchronizer> synchronizer);
        // Set clear color.
        void set_clear_color(Color const & clear_color);
        // Set blend mode.
        void set_blend_mode(BlendMode blend_mode);
        // Set cull face.
        void set_cull_face(CullFace cull_face);
        // Set depth mask.
        void set_depth_mask(bool depth_mask);
        // Set depth test.
        void set_depth_test(bool depth_test);
        // Set buffer.
        void set_buffer(std::shared_ptr<Buffer> buffer);
        // Set framebuffer, or nullptr to unbind.
        void set_framebuffer(std::shared_ptr<Framebuffer> framebuffer);
        // Set renderbuffer.
        void set_renderbuffer(std::shared_ptr<Renderbuffer> renderbuffer);
        // Set program, or nullptr to unbind.
        void set_program(std::shared_ptr<Program> program);
        // Set texture on specified texture unit.
        void set_texture(std::shared_ptr<Texture> texture, int unit = 0);
        // Set vertex array, or nullptr to unbind.
        void set_vertex_array(std::shared_ptr<VertexArray> vertex_array);
        // Set viewport.
        void set_viewport(Viewport const & viewport);
    private:
        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<GraphicsSynchronizer> synchronizer;
        Color clear_color;
        BlendMode blend_mode;
        CullFace cull_face;
        bool depth_mask;
        bool depth_test;
        std::shared_ptr<Buffer> buffer;
        std::shared_ptr<Framebuffer> framebuffer;
        std::shared_ptr<Renderbuffer> renderbuffer;
        std::shared_ptr<Program> program;
        TextureLookup textures;
        std::shared_ptr<VertexArray> vertex_array;
        Viewport viewport;
    };
}

#endif
