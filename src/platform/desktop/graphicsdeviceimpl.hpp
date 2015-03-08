#ifndef GRAPHICSDEVICEIMPL_HPP_INCLUDED
#define GRAPHICSDEVICEIMPL_HPP_INCLUDED

#include "graphicsdevice.hpp"
#include "translator.hpp"

namespace gst
{
    class GraphicsDeviceImpl : public GraphicsDevice {
    public:
        void clear(bool color, bool depth);

        void set_clear_color(Color const & clear_color);
        void set_blend_mode(BlendMode blend_mode);
        void set_cull_face(CullFace cull_face);
        void set_depth_mask(bool depth_mask);
        void set_depth_test(bool depth_test);
        void set_viewport(Viewport const & viewport);

        ResourceName create_shader(ShaderType type);
        void destroy_shader(ResourceName name);
        void compile_shader(ResourceName name, std::string const & source);
        bool get_compile_status(ResourceName name);
        std::string get_compile_error(ResourceName name);

        ResourceName create_program();
        void destroy_program(ResourceName name);
        void attach_shader(ResourceName program_name, ResourceName shader_name);
        void detach_shader(ResourceName program_name, ResourceName shader_name);
        void link_program(ResourceName name);
        bool get_link_status(ResourceName name);
        std::string get_link_error(ResourceName name);
        void bind_attribute_location(ResourceName program_name, int index, std::string const & name);
        int get_uniform_location(ResourceName program_name, std::string const & name);
        void uniform(int location, ShadowedData const & data);
        void use_program(ResourceName name);

        ResourceName create_buffer();
        void destroy_buffer(ResourceName name);
        void bind_buffer(ResourceName name, BufferTarget target);
        void buffer_data(BufferTarget target, ShadowedData const & data, DataUsage usage);

        ResourceName create_vertex_array();
        void destroy_vertex_array(ResourceName name);
        void bind_vertex_array(ResourceName name);
        void draw_arrays(DrawMode mode, int first, int count);
        void draw_elements(DrawMode mode, int count);
        void enable_vertex_attribute(VertexAttribute const & attribute);

        ResourceName create_renderbuffer();
        void destroy_renderbuffer(ResourceName name);
        void bind_renderbuffer(ResourceName name);
        void renderbuffer_storage(Resolution size, RenderbufferFormat format);

        ResourceName create_texture();
        void destroy_texture(ResourceName name);
        void bind_texture(ResourceName name, TextureTarget target, int unit);
        void update_texture_storage(Texture2D const & texture);
        void update_texture_storage(TextureCube const & texture);
        void update_texture_parameters(Texture const & texture);

        ResourceName create_framebuffer();
        void destroy_framebuffer(ResourceName name);
        void bind_framebuffer(ResourceName name);
        void framebuffer_texture_2d(ResourceName name);
        void framebuffer_renderbuffer(ResourceName name);
        std::vector<std::string> check_framebuffer_status() const;

        std::vector<std::string> get_errors() const;
    private:
        Translator translator;
    };
}

#endif
