#ifndef RENDERSTATE_HPP_INCLUDED
#define RENDERSTATE_HPP_INCLUDED

#include "blendmode.hpp"
#include "buffer.hpp"
#include "color.hpp"
#include "cullface.hpp"
#include "framebuffer.hpp"
#include "renderbuffer.hpp"
#include "program.hpp"
#include "texture.hpp"
#include "vertexarray.hpp"
#include "viewport.hpp"

#include <memory>
#include <unordered_map>
#include <vector>
#include <stack>

namespace gst
{
    class RenderStateImpl;
    class RenderTarget;

    typedef std::unordered_map<int, Texture> TextureLookup;

    struct StateSet {
        Color clear_color;
        BlendMode blend_mode;
        CullFace cull_face;
        bool depth_mask;
        bool depth_test;
        Buffer buffer;
        Framebuffer framebuffer;
        Renderbuffer renderbuffer;
        Texture texture0;
        VertexArray vertex_array;
        Viewport viewport;
    };

    typedef std::stack<StateSet> StateStack;

    class RenderState {
    public:
        RenderState(Viewport viewport);
        void push();
        void pop();
        void clear_buffers(bool color, bool depth);
        void set_clear_color(Color const & clear_color);
        void set_blend_mode(BlendMode blend_mode);
        void set_cull_face(CullFace cull_face);
        void set_depth_mask(bool depth_mask);
        void set_depth_test(bool depth_test);
        void set_buffer(Buffer & buffer);
        void set_framebuffer(Framebuffer & framebuffer);
        void set_renderbuffer(Renderbuffer & renderbuffer);
        void set_program(std::shared_ptr<Program> program);
        void set_texture(Texture & texture, int unit = 0);
        void set_texture(Framebuffer & framebuffer, int unit = 0);
        void set_texture(RenderTarget & target, int unit = 0);
        void set_vertex_array(VertexArray & vertex_array);
        void set_viewport(Viewport const & viewport);
        std::vector<std::string> check_errors() const;
    private:
        std::shared_ptr<RenderStateImpl> impl;
        StateStack stack;
        Color clear_color;
        BlendMode blend_mode;
        CullFace cull_face;
        bool depth_mask;
        bool depth_test;
        Buffer buffer;
        Framebuffer framebuffer;
        Renderbuffer renderbuffer;
        std::shared_ptr<Program> program;
        TextureLookup textures;
        VertexArray vertex_array;
        Viewport viewport;
    };
}

#endif
