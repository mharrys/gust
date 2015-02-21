#ifndef RENDERSTATEIMPL_HPP_INCLUDED
#define RENDERSTATEIMPL_HPP_INCLUDED

#include "blendmode.hpp"
#include "translator.hpp"

#include <vector>

namespace gst
{
    class Color;
    class FramebufferImpl;
    class ProgramImpl;
    class Viewport;

    class RenderStateImpl {
    public:
        void clear_buffers(bool color, bool depth);
        void set_clear_color(Color const & clear_color);
        void set_blend_mode(BlendMode blend_mode);
        void set_cull_face(CullFace cull_face);
        void set_depth_mask(bool depth_mask);
        void set_depth_test(bool depth_test);
        void set_framebuffer(FramebufferImpl & framebuffer);
        void set_framebuffer_none();
        void set_program_none();
        void set_viewport(Viewport const & viewport);
        std::vector<std::string> check_errors() const;
    private:
        Translator translator;
    };
}

#endif
