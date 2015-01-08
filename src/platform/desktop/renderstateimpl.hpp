#ifndef RENDERSTATEIMPL_HPP_INCLUDED
#define RENDERSTATEIMPL_HPP_INCLUDED

#include "translator.hpp"

#include <vector>

namespace gst
{
    class Color;
    class BufferImpl;
    class FramebufferImpl;
    class RenderbufferImpl;
    class ProgramImpl;
    class TextureImpl;
    class VertexArrayImpl;
    class Viewport;

    class RenderStateImpl {
    public:
        void clear_buffers(bool color, bool depth);
        void set_clear_color(Color const & clear_color);
        void set_cull_face(CullFace cull_face);
        void set_depth_mask(bool depth_mask);
        void set_depth_test(bool depth_test);
        void set_buffer(BufferImpl & buffer);
        void set_framebuffer(FramebufferImpl & framebuffer);
        void set_framebuffer_none();
        void set_renderbuffer(RenderbufferImpl & renderbuffer);
        void set_renderbuffer_none();
        void set_program(ProgramImpl & program);
        void set_program_none();
        void set_texture(TextureImpl & texture, int unit = 0);
        void set_vertex_array(VertexArrayImpl & vertex_array);
        void set_vertex_array_none();
        void set_viewport(Viewport const & viewport);
        std::vector<std::string> check_errors() const;
    private:
        Translator translator;
    };
}

#endif
