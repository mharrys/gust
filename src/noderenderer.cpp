#include "noderenderer.hpp"

#include "effect.hpp"
#include "lightnode.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "modelnode.hpp"
#include "pass.hpp"
#include "program.hpp"
#include "renderstate.hpp"

gst::NodeRenderer::NodeRenderer(
    std::shared_ptr<RenderState> render_state,
    glm::mat4 view,
    glm::mat4 projection,
    std::vector<LightNode> && lights)
    : render_state(render_state),
      view(view),
      projection(projection),
      lights(std::move(lights))
{
}

void gst::NodeRenderer::visit(ModelNode & node)
{
    MatrixState matrices;
    matrices.model = node.world_transform;
    matrices.view = view;
    matrices.model_view = matrices.view * matrices.model;
    matrices.projection = projection;
    matrices.normal = glm::inverseTranspose(glm::mat3(matrices.model_view));

    auto model = node.get_model();
    auto & mesh = model->mesh;
    auto & effect = model->effect;
    auto pass = effect.pass;

    for (unsigned int i = 0; i < effect.textures.size(); i++) {
        render_state->set_texture(effect.textures[i], i);
    }

    if (effect.uniforms) {
        pass->program->set_uniforms(*effect.uniforms);
    }
    pass->apply(matrices, lights);

    render_state->set_blend_mode(pass->blend_mode);
    render_state->set_cull_face(pass->cull_face);
    render_state->set_depth_mask(pass->depth_mask);
    render_state->set_depth_test(pass->depth_test);
    render_state->set_viewport(pass->viewport);
    render_state->set_program(pass->program);

    render_state->set_vertex_array(mesh.vertex_array);
    mesh.draw();
}
