#ifndef GRAPHICSDEVICEIMPL_HPP_INCLUDED
#define GRAPHICSDEVICEIMPL_HPP_INCLUDED

#include "graphicsdevice.hpp"
#include "translator.hpp"

namespace gst
{
    class GraphicsDeviceImpl : public GraphicsDevice {
    public:
        void clear(bool color, bool depth) final;

        void set_clear_color(Color const & clear_color) final;
        void set_blend_mode(BlendMode blend_mode) final;
        void set_cull_face(CullFace cull_face) final;
        void set_depth_mask(bool depth_mask) final;
        void set_depth_test(bool depth_test) final;
        void set_viewport(Viewport const & viewport) final;

        ResourceName create_shader(ShaderType type) final;
        void destroy_shader(ResourceName name) final;
        void compile_shader(ResourceName name, std::string const & source) final;
        bool get_compile_status(ResourceName name) final;
        std::string get_compile_error(ResourceName name) final;

        ResourceName create_program() final;
        void destroy_program(ResourceName name) final;
        void attach_shader(ResourceName program_name, ResourceName shader_name) final;
        void detach_shader(ResourceName program_name, ResourceName shader_name) final;
        void link_program(ResourceName name) final;
        bool get_link_status(ResourceName name) final;
        std::string get_link_error(ResourceName name) final;
        void bind_attribute_location(ResourceName program_name, int index, std::string const & name) final;
        int get_uniform_location(ResourceName program_name, std::string const & name) final;
        void uniform(int location, ShadowedData const & data) final;
        void use_program(ResourceName name) final;

        ResourceName create_buffer() final;
        void destroy_buffer(ResourceName name) final;
        void bind_buffer(ResourceName name, BufferTarget target) final;
        void buffer_data(BufferTarget target, ShadowedData const & data, DataUsage usage) final;

        ResourceName create_vertex_array() final;
        void destroy_vertex_array(ResourceName name) final;
        void bind_vertex_array(ResourceName name) final;
        void draw_arrays(DrawMode mode, int first, int count) final;
        void draw_elements(DrawMode mode, int count) final;
        void enable_vertex_attribute(VertexAttribute const & attribute) final;

        ResourceName create_renderbuffer() final;
        void destroy_renderbuffer(ResourceName name) final;
        void bind_renderbuffer(ResourceName name) final;
        void renderbuffer_storage(Resolution size, RenderbufferFormat format) final;

        ResourceName create_texture() final;
        void destroy_texture(ResourceName name) final;
        void bind_texture(ResourceName name, TextureTarget target, int unit) final;
        void update_texture_storage(
            TextureFormat internal_format,
            PixelFormat source_format,
            Resolution size,
            std::vector<unsigned char> const & data) final;
        void update_texture_storage(
            TextureFormat internal_format,
            PixelFormat source_format,
            Resolution size,
            std::vector<unsigned char> const & data,
            CubeFace face) final;
        void update_texture_min_filter(TextureTarget target, FilterMode min_filter) final;
        void update_texture_mag_filter(TextureTarget target, FilterMode mag_filter) final;
        void update_texture_wrap_s(TextureTarget target, WrapMode wrap_s) final;
        void update_texture_wrap_t(TextureTarget target, WrapMode wrap_t) final;
        void update_texture_wrap_r(TextureTarget target, WrapMode wrap_r) final;
        void update_texture_compare_func(TextureTarget target, CompareFunc compare_func) final;

        ResourceName create_framebuffer() final;
        void destroy_framebuffer(ResourceName name) final;
        void bind_framebuffer(ResourceName name) final;
        void attach_to_framebuffer(ResourceName attachment, AttachmentType type, AttachmentPoint point) final;
        std::vector<std::string> check_framebuffer_status() const final;

        std::vector<std::string> get_errors() const final;
    private:
        void update_texture_storage(
            GLenum target,
            GLenum internal_format,
            GLenum source_format,
            unsigned int width,
            unsigned int height,
            std::vector<unsigned char> const & data);

        Translator translator;
    };
}

#endif
