#ifndef GRAPHICSDEVICE_HPP_INCLUDED
#define GRAPHICSDEVICE_HPP_INCLUDED

#include "graphicsresource.hpp"
#include "vertexarray.hpp"

#include <string>
#include <vector>

namespace gst
{
    class Color;
    class Image;
    class Resolution;
    class ShadowedData;
    class Texture;
    class Texture2D;
    class TextureCube;
    class Viewport;

    enum class AttachmentType;
    enum class AttachmentPoint;
    enum class BlendMode;
    enum class BufferTarget;
    enum class CubeFace;
    enum class CullFace;
    enum class DataUsage;
    enum class PixelFormat;
    enum class RenderbufferFormat;
    enum class ShaderType;
    enum class TextureFormat;
    enum class TextureTarget;

    // The responsibility of this class is to interact with a graphics card.
    class GraphicsDevice {
    public:
        virtual ~GraphicsDevice() = default;

        // Clear buffers to present values.
        virtual void clear(bool color, bool depth) = 0;

        // Set clear values for color buffers.
        virtual void set_clear_color(Color const & clear_color) = 0;
        // Set blend mode enabled/disabled with appropiate blend function.
        virtual void set_blend_mode(BlendMode blend_mode) = 0;
        // Set faces that can be culled.
        virtual void set_cull_face(CullFace cull_face) = 0;
        // Set depth mask enabled/disabled.
        virtual void set_depth_mask(bool depth_mask) = 0;
        // Set depth test enabled/disabled.
        virtual void set_depth_test(bool depth_test) = 0;
        // Set viewport.
        virtual void set_viewport(Viewport const & viewport) = 0;

        // Return new shader object.
        virtual ResourceName create_shader(ShaderType type) = 0;
        // Destroy shader object.
        virtual void destroy_shader(ResourceName name) = 0;
        // Compile shader from specified source.
        virtual void compile_shader(ResourceName name, std::string const & source) = 0;
        // Return status from last compile operation.
        virtual bool get_compile_status(ResourceName name) = 0;
        // Return error message from last compile operation.
        virtual std::string get_compile_error(ResourceName name) = 0;

        // Return new program object.
        virtual ResourceName create_program() = 0;
        // Destroy program object.
        virtual void destroy_program(ResourceName name) = 0;
        // Attach specified shader object to specified program object.
        virtual void attach_shader(ResourceName program_name, ResourceName shader_name) = 0;
        // Attach specified shader object to specified program object.
        virtual void detach_shader(ResourceName program_name, ResourceName shader_name) = 0;
        // Link program object.
        virtual void link_program(ResourceName name) = 0;
        // Return status from last link operation.
        virtual bool get_link_status(ResourceName name) = 0;
        // Return error message from last compile operation.
        virtual std::string get_link_error(ResourceName name) = 0;
        // Bind vertex attribute index with a named attribute variable.
        virtual void bind_attribute_location(ResourceName program_name, int index, std::string const & name) = 0;
        // Return uniform location from specified name.
        virtual int get_uniform_location(ResourceName program_name, std::string const & name) = 0;
        // Modify value of uniform.
        virtual void uniform(int location, ShadowedData const & data) = 0;
        // Install specified program object as part of current rendering state.
        virtual void use_program(ResourceName name) = 0;

        // Return new buffer object.
        virtual ResourceName create_buffer() = 0;
        // Destroy buffer object.
        virtual void destroy_buffer(ResourceName name) = 0;
        // Bind buffer object.
        virtual void bind_buffer(ResourceName name, BufferTarget target) = 0;
        // Buffer data to current bound buffer object.
        virtual void buffer_data(BufferTarget target, ShadowedData const & data, DataUsage usage) = 0;

        // Return new vertex array object.
        virtual ResourceName create_vertex_array() = 0;
        // Destroy vertex array object.
        virtual void destroy_vertex_array(ResourceName name) = 0;
        // Bind vertex array object.
        virtual void bind_vertex_array(ResourceName name) = 0;
        // Render primitives from stored array data.
        virtual void draw_arrays(DrawMode mode, int first, int count) = 0;
        // Render primitives from stored array data.
        virtual void draw_elements(DrawMode mode, int count) = 0;
        // Enable and define generic vertex attribute.
        virtual void enable_vertex_attribute(VertexAttribute const & attribute) = 0;

        // Return new renderbuffer object.
        virtual ResourceName create_renderbuffer() = 0;
        // Destroy renderbuffer object.
        virtual void destroy_renderbuffer(ResourceName name) = 0;
        // Bind renderbuffer object.
        virtual void bind_renderbuffer(ResourceName name) = 0;
        // Establish data storage of specified format and dimensions for renderbuffer objects image.
        virtual void renderbuffer_storage(Resolution size, RenderbufferFormat format) = 0;

        // Create new texture object.
        virtual ResourceName create_texture() = 0;
        // Destroy texture object.
        virtual void destroy_texture(ResourceName name) = 0;
        // Bind texture object.
        virtual void bind_texture(ResourceName name, TextureTarget target, int unit) = 0;
        // Update texture storage for 2-dimensional texture.
        virtual void update_texture_storage(
            TextureFormat internal_format,
            PixelFormat source_format,
            Resolution size,
            std::vector<unsigned char> data) = 0;
        // Update texture storage for texture cube face.
        virtual void update_texture_storage(
            TextureFormat internal_format,
            PixelFormat source_format,
            Resolution size,
            std::vector<unsigned char> data,
            CubeFace face) = 0;
        // Update texture parameters.
        virtual void update_texture_parameters(Texture const & texture) = 0;

        // Create new framebuffer object.
        virtual ResourceName create_framebuffer() = 0;
        // Destroy framebuffer object.
        virtual void destroy_framebuffer(ResourceName name) = 0;
        // Bind framebuffer object.
        virtual void bind_framebuffer(ResourceName name) = 0;
        // Attach a texture/renderbuffer object to the currently bound framebuffer object.
        virtual void attach_to_framebuffer(ResourceName attachment, AttachmentType type, AttachmentPoint point) = 0;
        // Return array of status messages for currently bound framebuffer object.
        virtual std::vector<std::string> check_framebuffer_status() const = 0;

        // Return array of error messages (if any).
        virtual std::vector<std::string> get_errors() const = 0;
    };
}

#endif
