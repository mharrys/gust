#ifndef GRAPHICSSYNCHRONIZER_HPP_INCLUDED
#define GRAPHICSSYNCHRONIZER_HPP_INCLUDED

#include "graphicsresource.hpp"

#include <memory>
#include <unordered_map>

namespace gst
{
    class Buffer;
    class Framebuffer;
    class FramebufferAttachment;
    class GraphicsDevice;
    class Logger;
    class Renderbuffer;
    class Program;
    class Shader;
    class Texture;
    class Texture2D;
    class TextureCube;
    class VertexArray;

    enum class AttachmentPoint;

    typedef std::unordered_map<std::string, int> LocationCache;
    typedef std::unordered_map<ResourceName, LocationCache> ProgramLocationCache;

    // The responsibility of this class is to synchronize client state of
    // mirrored graphics resources with the graphics card.
    class GraphicsSynchronizer {
    public:
        GraphicsSynchronizer(
            std::shared_ptr<GraphicsDevice> device,
            std::shared_ptr<Logger> logger);
        // Bind buffer with identifer on the graphics card.
        void bind(Buffer & buffer);
        // Bind framebuffer with identifer on the graphics card.
        void bind(Framebuffer & framebuffer);
        // Bind program and its shaders with identifiers on the graphics card.
        void bind(Program & program);
        // Bind renderbuffer with identifer on the graphics card.
        void bind(Renderbuffer & renderbuffer);
        // Bind shader with identifer on the graphics card.
        void bind(Shader & shader);
        // Bind texture on texture unit with identifer on the graphics card.
        void bind(Texture & texture, int unit);
        // Bind vertex array with identifer on the graphics card.
        void bind(VertexArray & vertex_array);
        // Replace graphics card state with specified buffer.
        void update(Buffer & buffer);
        // Replace graphics card state with specified framebuffer.
        void update(Framebuffer & framebuffer);
        // Replace graphics card state with specified program.
        void update(Program & program);
        // Replace graphics card state with specified renderbuffer.
        void update(Renderbuffer & renderbuffer);
        // Replace graphics card state with specified shader.
        void update(Shader & shader);
        // Replace graphics card state with specified texture.
        void update(Texture & texture);
        // Replace graphics card state with specified vertex array.
        void update(VertexArray & vertex_array);
    private:
        int get_cached_uniform_location(
            ResourceName name,
            std::string const & annotation);
        void attach(
            FramebufferAttachment const & attachment,
            AttachmentPoint attachment_point);
        void update_storage(Texture2D const & texture);
        void update_storage(TextureCube const & texture);

        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<Logger> logger;
        ProgramLocationCache program_location_cache;
    };
}

#endif
