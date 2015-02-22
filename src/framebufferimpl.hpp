#ifndef FRAMEBUFFERIMPL_HPP_INCLUDED
#define FRAMEBUFFERIMPL_HPP_INCLUDED

#include "framebuffer.hpp"

namespace gst
{
    class FramebufferImpl : public Framebuffer {
    public:
        FramebufferImpl(std::shared_ptr<GraphicsDevice> device);
        ~FramebufferImpl();
        void attach(std::shared_ptr<Texture> color);
        void attach(std::shared_ptr<Renderbuffer> depth);
        std::shared_ptr<Texture> get_color() const;
        std::shared_ptr<Renderbuffer> get_depth() const;
        std::vector<std::string> get_status() const;
    private:
        void bind();
        void sync(RenderState & render_state);

        FramebufferHandle handle;
        std::shared_ptr<GraphicsDevice> device;

        std::shared_ptr<Texture> color;
        std::shared_ptr<Renderbuffer> depth;
        bool color_dirty;
        bool depth_dirty;
        std::vector<std::string> status;
    };
}

#endif
