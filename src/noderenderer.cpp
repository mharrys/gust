#include "noderenderer.hpp"

#include "effect.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "modelnode.hpp"
#include "program.hpp"
#include "renderstate.hpp"

gst::NodeRenderer::NodeRenderer(
    std::shared_ptr<RenderState> render_state,
    ModelState && state)
    : render_state(render_state),
      state(std::move(state))
{
}

void gst::NodeRenderer::visit(ModelNode & node)
{
    state.model = node.world_transform;
    state.model_view = state.view * state.model;
    state.normal = glm::inverseTranspose(glm::mat3(state.model_view));

    auto & mesh = node.get_mesh();
    auto & effect = node.get_effect();
    auto pass = effect.pass;

    for (unsigned int i = 0; i < effect.textures.size(); i++) {
        render_state->set_texture(effect.textures[i], i);
    }

    if (effect.uniforms) {
        pass->program->set_uniforms(*effect.uniforms);
    }
    pass->apply(state);

    render_state->set_blend_mode(pass->blend_mode);
    render_state->set_cull_face(pass->cull_face);
    render_state->set_depth_mask(pass->depth_mask);
    render_state->set_depth_test(pass->depth_test);
    render_state->set_viewport(pass->viewport);
    render_state->set_program(pass->program);
    render_state->set_vertex_array(mesh.vertex_array);

    mesh.draw();
}
