#ifndef GRAPHICSDEVICEIMPL_HPP_INCLUDED
#define GRAPHICSDEVICEIMPL_HPP_INCLUDED

#include "graphicsdevice.hpp"
#include "translator.hpp"

namespace gst
{
    class GraphicsDeviceImpl : public GraphicsDevice {
    public:
        void clear(bool color, bool depth);
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
        BufferHandle create_buffer();
        void destroy_buffer(BufferHandle buffer);
        void bind_buffer(BufferHandle buffer, BufferTarget target);
        void buffer_data(BufferTarget target, ShadowedData const & data, DataUsage usage);
        VertexArrayHandle create_vertex_array();
        void destroy_vertex_array(VertexArrayHandle vertex_array);
        void bind_vertex_array(VertexArrayHandle vertex_array);
        void draw_arrays(DrawMode mode, int first, int count);
        void draw_elements(DrawMode mode, int count);
        void enable_vertex_attribute(VertexAttribute const & attribute);
        RenderbufferHandle create_renderbuffer();
        void destroy_renderbuffer(RenderbufferHandle renderbuffer);
        void bind_renderbuffer(RenderbufferHandle renderbuffer);
        void renderbuffer_storage(Resolution size, RenderbufferFormat format);
        TextureHandle create_texture();
        void destroy_texture(TextureHandle texture);
        void bind_texture(TextureHandle texture, TextureTarget target, int unit);
        void texture_image_2d(TextureTarget target, Image const & image, TextureParam const & param);
        void texture_parameters(TextureTarget target, TextureParam const & param);
        FramebufferHandle create_framebuffer();
        void destroy_framebuffer(FramebufferHandle framebuffer);
        void bind_framebuffer(FramebufferHandle framebuffer);
        void framebuffer_texture_2d(TextureHandle texture);
        void framebuffer_renderbuffer(RenderbufferHandle renderbuffer);
        std::vector<std::string> check_framebuffer_status();
    private:
        Translator translator;
    };
}

#endif
