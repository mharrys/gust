#ifndef FRAMEBUFFER_HPP_INCLUDED
#define FRAMEBUFFER_HPP_INCLUDED

#include "renderbuffer.hpp"
#include "texture.hpp"

#include <memory>
#include <string>
#include <vector>

namespace gst
{
    class RenderState;
    class Renderbuffer;
    class Texture;

    // The responsibility of this class is to mirror a framebuffer object on
    // the graphics card.
    class Framebuffer {
        friend RenderState;
    public:
        virtual ~Framebuffer() = default;
        // Attach color.
        virtual void attach(std::shared_ptr<Texture> color) = 0;
        // Attach depth.
        virtual void attach(std::shared_ptr<Renderbuffer> depth) = 0;
        // Return attached color.
        virtual std::shared_ptr<Texture> get_color() const = 0;
        // Return attached depth.
        virtual std::shared_ptr<Renderbuffer> get_depth() const = 0;
        // Return cached status from last sync.
        virtual std::vector<std::string> get_status() const = 0;
    private:
        // Notify graphics card to bind this framebuffer.
        virtual void bind() = 0;
        // Sync client state with graphics card.
        virtual void sync(RenderState & render_state) = 0;
    };
}

#endif
