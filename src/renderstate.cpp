#include "renderstate.hpp"

#include "buffer.hpp"
#include "framebuffer.hpp"
#include "framebufferattachment.hpp"
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
            synchronizer->bind(*framebuffer);
        } else {
            device->bind_framebuffer(0);
        }
    }

    if (framebuffer) {
        // keep attachment up-to-date
        set_framebuffer_attachment(framebuffer->get_color());
        set_framebuffer_attachment(framebuffer->get_depth());
        synchronizer->update(*framebuffer);
    }
}

void gst::RenderState::set_renderbuffer(std::shared_ptr<Renderbuffer> renderbuffer)
{
    if (this->renderbuffer != renderbuffer) {
        this->renderbuffer = renderbuffer;
        synchronizer->bind(*renderbuffer);
    }
    synchronizer->update(*renderbuffer);
}

void gst::RenderState::set_program(std::shared_ptr<Program> program)
{
    if (this->program != program) {
        this->program = program;
        synchronizer->bind(*program);
    }
    synchronizer->update(*program);
}

void gst::RenderState::set_texture(std::shared_ptr<Texture> texture, int unit)
{
    auto current = textures.count(unit) > 0 ? textures.at(unit) : nullptr;

    if (current != texture) {
        textures[unit] = texture;
        synchronizer->bind(*texture, unit);
    }
    synchronizer->update(*texture);
}

void gst::RenderState::set_vertex_array(std::shared_ptr<VertexArray> vertex_array)
{
    if (this->vertex_array != vertex_array) {
        this->vertex_array = vertex_array;
        synchronizer->bind(*vertex_array);
    }
    synchronizer->update(*vertex_array);
}

void gst::RenderState::set_viewport(Viewport const & viewport)
{
    if (this->viewport != viewport) {
        this->viewport = viewport;
        device->set_viewport(viewport);
    }
}

void gst::RenderState::set_framebuffer_attachment(FramebufferAttachment const & attachment)
{
    auto resource = attachment.get_attachment();

    if (!resource) {
        return;
    }

    if (attachment.get_type() == AttachmentType::RENDERBUFFER) {
        set_renderbuffer(std::static_pointer_cast<Renderbuffer>(resource));
    } else {
        set_texture(std::static_pointer_cast<Texture>(resource));
    }
}
