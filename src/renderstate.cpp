#include "renderstate.hpp"

#include "renderstateimpl.hpp"
#include "rendertarget.hpp"

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
    impl->set_renderbuffer_none();
    impl->set_program_none();
    impl->set_texture_none();
    impl->set_viewport(viewport);
    impl->set_vertex_array_none();
}

void gst::RenderState::push()
{
    // temporary binds shall only be done on texture unit 0
    auto texture0 = textures.count(0) > 0 ? textures[0] : Texture();
    stack.push({
        clear_color,
        blend_mode,
        cull_face,
        depth_mask,
        depth_test,
        buffer,
        framebuffer,
        renderbuffer,
        program,
        texture0,
        vertex_array,
        viewport
    });
}

void gst::RenderState::pop()
{
    if (!stack.empty()) {
        auto state = stack.top();
        stack.pop();
        set_clear_color(state.clear_color);
        set_blend_mode(state.blend_mode);
        set_cull_face(state.cull_face);
        set_depth_mask(state.depth_mask);
        set_depth_test(state.depth_test);
        set_buffer(state.buffer);
        set_framebuffer(state.framebuffer);
        set_renderbuffer(state.renderbuffer);
        set_program(state.program);
        set_texture(state.texture0);
        set_vertex_array(state.vertex_array);
        set_viewport(state.viewport);
    }
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

void gst::RenderState::set_buffer(Buffer & buffer)
{
    // do not bother rebinding empty buffers
    if (!buffer) {
        return;
    }

    if (this->buffer != buffer) {
        this->buffer = buffer;
        impl->set_buffer(*buffer.impl.get());
        buffer.refresh();
    }
}

void gst::RenderState::set_framebuffer(Framebuffer & framebuffer)
{
    if (this->framebuffer != framebuffer) {
        this->framebuffer = framebuffer;
        if (framebuffer) {
            impl->set_framebuffer(*framebuffer.impl.get());
            framebuffer.refresh(*this);
        } else {
            impl->set_framebuffer_none();
        }
    }
}

void gst::RenderState::set_renderbuffer(Renderbuffer & renderbuffer)
{
    // do not bother rebinding empty renderbuffer
    if (!renderbuffer) {
        return;
    }

    if (this->renderbuffer != renderbuffer) {
        this->renderbuffer = renderbuffer;
        if (renderbuffer) {
            impl->set_renderbuffer(*renderbuffer.impl.get());
            renderbuffer.refresh();
        }
    }
}

void gst::RenderState::set_program(Program & program)
{
    if (this->program != program) {
        this->program = program;
        if (program) {
            impl->set_program(*program.impl.get());
        } else {
            impl->set_program_none();
        }
    }
}

void gst::RenderState::set_texture(Texture & texture, int unit)
{
    // do not bother rebinding empty texture
    if (!texture) {
        return;
    }

    Texture current;
    if (textures.count(unit) > 0) {
        current = textures.at(unit);
    }

    if (current != texture) {
        textures[unit] = texture;
        if (texture) {
            impl->set_texture(*texture.impl.get(), unit);
            texture.refresh();
        }
    }
}

void gst::RenderState::set_texture(Framebuffer & framebuffer, int unit)
{
    set_texture(framebuffer.color, unit);
}

void gst::RenderState::set_texture(RenderTarget & target, int unit)
{
    set_texture(target.framebuffer, unit);
}

void gst::RenderState::set_vertex_array(VertexArray & vertex_array)
{
    if (this->vertex_array != vertex_array) {
        this->vertex_array = vertex_array;
        if (vertex_array) {
            impl->set_vertex_array(*vertex_array.impl.get());
            vertex_array.refresh(*this);
        } else {
            impl->set_vertex_array_none();
        }
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
