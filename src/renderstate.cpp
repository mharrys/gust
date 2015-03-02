#include "renderstate.hpp"

#include "buffer.hpp"
#include "framebuffer.hpp"
#include "graphicsdevice.hpp"
#include "graphicssynchronizer.hpp"
#include "program.hpp"
#include "renderbuffer.hpp"
#include "texture.hpp"
#include "vertexarray.hpp"

gst::RenderState::RenderState(
    std::shared_ptr<GraphicsDevice> device,
    std::shared_ptr<GraphicsSynchronizer> synchronizer)
    : device(device),
      synchronizer(synchronizer),
      clear_color(0.0f, 0.0f, 0.0f, 0.0f),
      blend_mode(BlendMode::NONE),
      cull_face(CullFace::NONE),
      depth_mask(true),
      depth_test(false)
{
    set_clear_color(clear_color);
    set_blend_mode(blend_mode);
    set_cull_face(cull_face);
    set_depth_mask(depth_mask);
    set_depth_test(depth_test);
    set_framebuffer(nullptr);
    set_program(nullptr);
    set_viewport(viewport);
}

void gst::RenderState::set_clear_color(Color const & clear_color)
{
    if (this->clear_color != clear_color) {
        this->clear_color = clear_color;
        device->set_clear_color(clear_color);
    }
}

void gst::RenderState::set_blend_mode(BlendMode blend_mode)
{
    if (this->blend_mode != blend_mode) {
        this->blend_mode = blend_mode;
        device->set_blend_mode(blend_mode);
    }
}

void gst::RenderState::set_cull_face(CullFace cull_face)
{
    if (this->cull_face != cull_face) {
        this->cull_face = cull_face;
        device->set_cull_face(cull_face);
    }
}

void gst::RenderState::set_depth_mask(bool depth_mask)
{
    if (this->depth_mask != depth_mask) {
        this->depth_mask = depth_mask;
        device->set_depth_mask(depth_mask);
    }
}

void gst::RenderState::set_depth_test(bool depth_test)
{
    if (this->depth_test != depth_test) {
        this->depth_test = depth_test;
        device->set_depth_test(depth_test);
    }
}

void gst::RenderState::set_framebuffer(std::shared_ptr<Framebuffer> framebuffer)
{
    if (this->framebuffer != framebuffer) {
        this->framebuffer = framebuffer;
        if (framebuffer) {
            set_texture(framebuffer->get_color());
            set_renderbuffer(framebuffer->get_depth());
            synchronizer->sync(*framebuffer);
        } else {
            device->bind_framebuffer(0);
        }
    }
}

void gst::RenderState::set_renderbuffer(std::shared_ptr<Renderbuffer> renderbuffer)
{
    if (this->renderbuffer != renderbuffer) {
        this->renderbuffer = renderbuffer;
        if (renderbuffer) {
            synchronizer->sync(*renderbuffer);
        }
    }
}

void gst::RenderState::set_program(std::shared_ptr<Program> program)
{
    if (this->program != program) {
        this->program = program;
        if (this->program) {
            synchronizer->sync(*program);
        } else {
            device->use_program({ 0 });
        }
    }
}

void gst::RenderState::set_texture(std::shared_ptr<Texture> texture, int unit)
{
    auto current = textures.count(unit) > 0 ? textures.at(unit) : nullptr;

    if (current != texture) {
        textures[unit] = texture;
        if (texture) {
            synchronizer->sync(*texture, unit);
        }
    }
}

void gst::RenderState::set_vertex_array(std::shared_ptr<VertexArray> vertex_array)
{
    if (this->vertex_array != vertex_array) {
        this->vertex_array = vertex_array;
        synchronizer->sync(*vertex_array);
    }
}

void gst::RenderState::set_viewport(Viewport const & viewport)
{
    if (this->viewport != viewport) {
        this->viewport = viewport;
        device->set_viewport(viewport);
    }
}
