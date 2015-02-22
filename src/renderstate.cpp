#include "renderstate.hpp"

#include "renderstateimpl.hpp"

gst::RenderState::RenderState(Viewport viewport)
    : impl(std::make_shared<RenderStateImpl>()),
      clear_color(0.0f, 0.0f, 0.0f, 0.0f),
      blend_mode(BlendMode::NONE),
      cull_face(CullFace::NONE),
      depth_mask(true),
      depth_test(false),
      viewport(viewport)
{
    impl->set_clear_color(clear_color);
    impl->set_blend_mode(blend_mode);
    impl->set_cull_face(cull_face);
    impl->set_depth_mask(depth_mask);
    impl->set_depth_test(depth_test);
    impl->set_framebuffer_none();
    impl->set_viewport(viewport);
}

void gst::RenderState::clear_buffers(bool color, bool depth)
{
    impl->clear_buffers(color, depth);
}

void gst::RenderState::set_clear_color(Color const & clear_color)
{
    if (this->clear_color != clear_color) {
        this->clear_color = clear_color;
        impl->set_clear_color(clear_color);
    }
}

void gst::RenderState::set_blend_mode(BlendMode blend_mode)
{
    if (this->blend_mode != blend_mode) {
        this->blend_mode = blend_mode;
        impl->set_blend_mode(blend_mode);
    }
}

void gst::RenderState::set_cull_face(CullFace cull_face)
{
    if (this->cull_face != cull_face) {
        this->cull_face = cull_face;
        impl->set_cull_face(cull_face);
    }
}

void gst::RenderState::set_depth_mask(bool depth_mask)
{
    if (this->depth_mask != depth_mask) {
        this->depth_mask = depth_mask;
        impl->set_depth_mask(depth_mask);
    }
}

void gst::RenderState::set_depth_test(bool depth_test)
{
    if (this->depth_test != depth_test) {
        this->depth_test = depth_test;
        impl->set_depth_test(depth_test);
    }
}

void gst::RenderState::set_buffer(std::shared_ptr<Buffer> buffer)
{
    if (this->buffer != buffer) {
        this->buffer = buffer;
        this->buffer->bind();
        this->buffer->sync();
    }
}

void gst::RenderState::set_framebuffer(Framebuffer & framebuffer)
{
    if (this->framebuffer != framebuffer) {
        impl->set_framebuffer(*framebuffer.impl.get());
        framebuffer.refresh(*this);
    }
}

void gst::RenderState::set_framebuffer_none()
{
    impl->set_framebuffer_none();
}

void gst::RenderState::set_renderbuffer(std::shared_ptr<Renderbuffer> renderbuffer)
{
    if (this->renderbuffer != renderbuffer) {
        this->renderbuffer = renderbuffer;
        this->renderbuffer->bind();
        this->renderbuffer->sync();
    }
}

void gst::RenderState::set_program(std::shared_ptr<Program> program)
{
    if (this->program != program) {
        this->program = program;
        this->program->use();
    }
}

void gst::RenderState::set_texture(std::shared_ptr<Texture> texture, int unit)
{
    std::shared_ptr<Texture> current;
    if (textures.count(unit) > 0) {
        current = textures.at(unit);
    }

    if (current != texture) {
        textures[unit] = texture;
        texture->bind(unit);
        texture->sync();
    }
}

void gst::RenderState::set_texture(Framebuffer & framebuffer, int unit)
{
    set_texture(framebuffer.color, unit);
}

void gst::RenderState::set_vertex_array(std::shared_ptr<VertexArray> vertex_array)
{
    if (this->vertex_array != vertex_array) {
        this->vertex_array = vertex_array;
        this->vertex_array->bind();
        this->vertex_array->sync(*this);
    }
}

void gst::RenderState::set_viewport(Viewport const & viewport)
{
    if (this->viewport != viewport) {
        this->viewport = viewport;
        impl->set_viewport(viewport);
    }
}

std::vector<std::string> gst::RenderState::check_errors() const
{
    return impl->check_errors();
}
