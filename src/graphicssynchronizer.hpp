#ifndef GRAPHICSSYNCHRONIZER_HPP_INCLUDED
#define GRAPHICSSYNCHRONIZER_HPP_INCLUDED

#include <memory>
#include <unordered_map>

namespace gst
{
    class Buffer;
    class Framebuffer;
    class GraphicsDevice;
    class Logger;
    class Renderbuffer;
    class Program;
    class Shader;
    class Texture;
    class VertexArray;

    // The responsibility of this class is to synchronize client state of
    // mirrored graphics resources with the graphics card.
    class GraphicsSynchronizer {
    public:
        GraphicsSynchronizer(
            std::shared_ptr<GraphicsDevice> device,
            std::shared_ptr<Logger> logger);
        // Replace graphics card state with specified buffer.
        void sync(Buffer & buffer);
        // Replace graphics card state with specified renderbuffer.
        void sync(Renderbuffer & renderbuffer);
        // Replace graphics card state with specified program.
        void sync(Program & program);
        // Replace graphics card state with specified shader.
        void sync(Shader & shader);
        // Replace graphics card state with specified texture.
        void sync(Texture & texture, int unit);
        // Replace graphics card state with specified framebuffer.
        void sync(Framebuffer & framebuffer);
        // Replace graphics card state with specified vertex array.
        void sync(VertexArray & vertex_array);
    private:
        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<Logger> logger;
    };
}

#endif
