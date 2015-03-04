#ifndef GRAPHICSDEVICE_HPP_INCLUDED
#define GRAPHICSDEVICE_HPP_INCLUDED

#include "blendmode.hpp"
#include "buffer.hpp"
#include "cullface.hpp"
#include "graphicsresource.hpp"
#include "renderbuffer.hpp"
#include "shadertype.hpp"
#include "textureparam.hpp"
#include "vertexarray.hpp"

#include <string>
#include <vector>

namespace gst
{
    class Color;
    class Image;
    class Resolution;
    class ShadowedData;
    class Viewport;

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
        // Modify value of int uniform.
        virtual void uniform_int(int location, int value) = 0;
        // Modify value of float uniform.
        virtual void uniform_float(int location, float value) = 0;
        // Modify value of vec2 uniform.
        virtual void uniform_vec2(int location, glm::vec2 const & value) = 0;
        // Modify value of vec3 uniform.
        virtual void uniform_vec3(int location, glm::vec3 const & value) = 0;
        // Modify value of vec4 uniform.
        virtual void uniform_vec4(int location, glm::vec4 const & value) = 0;
        // Modify value of int array uniform.
        virtual void uniform_int_array(int location, std::vector<int> const & value) = 0;
        // Modify value of float array uniform.
        virtual void uniform_float_array(int location, std::vector<float> const & value) = 0;
        // Modify value of matrix uniform.
        virtual void uniform_matrix3(int location, int count, bool transpose, std::vector<float> const & value) = 0;
        // Modify value of matrix uniform.
        virtual void uniform_matrix4(int location, int count, bool transpose, std::vector<float> const & value) = 0;
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
        // Specify 2D texture image.
        virtual void texture_image_2d(TextureTarget target, Image const & image, TextureParam const & param) = 0;
        // Set texture parameters.
        virtual void texture_parameters(TextureTarget target, TextureParam const & param) = 0;

        // Create new framebuffer object.
        virtual ResourceName create_framebuffer() = 0;
        // Destroy framebuffer object.
        virtual void destroy_framebuffer(ResourceName name) = 0;
        // Bind framebuffer object.
        virtual void bind_framebuffer(ResourceName name) = 0;
        // Attach a level of a texture object to the currently bound
        // framebuffer object.
        virtual void framebuffer_texture_2d(ResourceName name) = 0;
        // Attach a renderbuffer object to the currently bound framebuffer
        // object.
        virtual void framebuffer_renderbuffer(ResourceName name) = 0;
        // Return array of status messages for currently bound framebuffer object.
        virtual std::vector<std::string> check_framebuffer_status() const = 0;

        // Return array of error messages (if any).
        virtual std::vector<std::string> get_errors() const = 0;
    };
}

#endif
