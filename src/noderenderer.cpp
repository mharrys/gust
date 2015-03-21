#include "noderenderer.hpp"

#include "graphicsdevice.hpp"
#include "indexbuffer.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "modelnode.hpp"
#include "program.hpp"
#include "renderstate.hpp"
#include "vertexbuffer.hpp"

gst::NodeRenderer::NodeRenderer(
    std::shared_ptr<GraphicsDevice> device,
    std::shared_ptr<RenderState> render_state,
    ModelState && state)
    : device(device),
      render_state(render_state),
      state(std::move(state)),
      use_effect_override(false)
{
}

void gst::NodeRenderer::visit(ModelNode & node)
{
    state.model = node.world_transform;
    state.model_view = state.view * state.model;
    state.normal = glm::inverseTranspose(glm::mat3(state.model_view));

    auto & mesh = node.get_mesh();
    auto & effect = use_effect_override ? effect_override : node.get_effect();
    auto & pass = effect.get_pass();
    auto & textures = effect.get_textures();

    // set textures at the texture unit in the order they are stored in,
    // effect uniforms will associate which unit belongs to which annotation
    for (auto i = 0u; i < textures.size(); i++) {
        render_state->set_texture(textures[i], i);
    }

    pass.program->set_uniforms(effect.get_uniforms());
    pass.apply(state);

    render_state->set_blend_mode(pass.blend_mode);
    render_state->set_cull_face(pass.cull_face);
    render_state->set_depth_mask(pass.depth_mask);
    render_state->set_depth_test(pass.depth_test);
    render_state->set_viewport(pass.viewport);
    render_state->set_program(pass.program);
    render_state->set_vertex_array(mesh.vertex_array);

    if (mesh.index) {
        device->draw_elements(mesh.mode, mesh.index->get_count());
    } else {
        device->draw_arrays(mesh.mode, 0, mesh.positions->get_count());
    }
}

void gst::NodeRenderer::set_effect_override(Effect & effect)
{
    effect_override = effect;
    use_effect_override = true;
}
