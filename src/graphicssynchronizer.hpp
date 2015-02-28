#ifndef GRAPHICSSYNCHRONIZER_HPP_INCLUDED
#define GRAPHICSSYNCHRONIZER_HPP_INCLUDED

#include <memory>

namespace gst
{
    class Framebuffer;
    class GraphicsDevice;
    class Renderbuffer;
    class Texture;

    // The responsibility of this class is to synchronize client state of
    // mirrored graphics resources with the graphics card.
    class GraphicsSynchronizer {
    public:
        GraphicsSynchronizer(std::shared_ptr<GraphicsDevice> device);
        // Replace graphics card state with specified renderbuffer.
        void sync(Renderbuffer & renderbuffer);
        // Replace graphics card state with specified texture.
        void sync(Texture & texture, int unit);
        // Replace graphics card state with specified framebuffer.
        void sync(Framebuffer & framebuffer);
    private:
        std::shared_ptr<GraphicsDevice> device;
    };
}

#endif
