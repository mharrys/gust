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

        ShaderHandle create_shader(ShaderType type);
        void destroy_shader(ShaderHandle shader);
        void compile_shader(ShaderHandle shader, std::string const & source);
        bool get_compile_status(ShaderHandle shader);
        std::string get_compile_error(ShaderHandle shader);

        ProgramHandle create_program();
        void destroy_program(ProgramHandle program);
        void attach_shader(ProgramHandle program, ShaderHandle shader);
        void detach_shader(ProgramHandle program, ShaderHandle shader);
        void link_program(ProgramHandle program);
        bool get_link_status(ProgramHandle program);
        std::string get_link_error(ProgramHandle program);
        void bind_attribute_location(ProgramHandle program, int index, std::string const & name);
        int get_uniform_location(ProgramHandle program, std::string const & name);
        void uniform_int(int location, int value);
        void uniform_float(int location, float value);
        void uniform_vec2(int location, glm::vec2 const & value);
        void uniform_vec3(int location, glm::vec3 const & value);
        void uniform_vec4(int location, glm::vec4 const & value);
        void uniform_int_array(int location, std::vector<int> const & value);
        void uniform_float_array(int location, std::vector<float> const & value);
        void uniform_matrix3(int location, int count, bool transpose, std::vector<float> const & value);
        void uniform_matrix4(int location, int count, bool transpose, std::vector<float> const & value);
        void use_program(ProgramHandle program);

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
        void texture_image_2d(TextureTarget target, Image const & image, TextureParam const & param);
        void texture_parameters(TextureTarget target, TextureParam const & param);

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
