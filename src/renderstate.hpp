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
    class Program;
    class Renderbuffer;
    class Texture;
    class VertexArray;

    typedef std::unordered_map<int, std::shared_ptr<Texture>> TextureLookup;

    class RenderState {
    public:
        RenderState(std::shared_ptr<GraphicsDevice> device);
        void clear_buffers(bool color, bool depth);
        void set_clear_color(Color const & clear_color);
        void set_blend_mode(BlendMode blend_mode);
        void set_cull_face(CullFace cull_face);
        void set_depth_mask(bool depth_mask);
        void set_depth_test(bool depth_test);
        void set_buffer(std::shared_ptr<Buffer> buffer);
        void set_framebuffer(std::shared_ptr<Framebuffer> framebuffer);
        void set_renderbuffer(std::shared_ptr<Renderbuffer> renderbuffer);
        void set_program(std::shared_ptr<Program> program);
        void set_texture(std::shared_ptr<Texture> texture, int unit = 0);
        void set_vertex_array(std::shared_ptr<VertexArray> vertex_array);
        void set_viewport(Viewport const & viewport);
        std::vector<std::string> check_errors() const;
    private:
        std::shared_ptr<GraphicsDevice> device;
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
