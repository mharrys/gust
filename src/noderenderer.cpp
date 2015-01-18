#include "noderenderer.hpp"

#include "camera.hpp"
#include "cameranode.hpp"
#include "effect.hpp"
#include "lightnode.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "modelnode.hpp"
#include "pass.hpp"
#include "renderstate.hpp"
#include "technique.hpp"

gst::NodeRenderer::NodeRenderer(
    std::shared_ptr<RenderState> render_state,
    std::shared_ptr<CameraNode> eye,
    std::vector<LightNode> lights)
    : render_state(render_state),
      eye(eye),
      lights(std::move(lights))
{
}

void gst::NodeRenderer::visit(ModelNode & node)
{
    if (!node.enabled) {
        return;
    }

    MatrixState matrices;
    matrices.model = node.world_transform;
    matrices.view = eye->get_view();
    matrices.model_view = matrices.view * matrices.model;
    matrices.projection = eye->get_projection();
    matrices.normal = glm::inverseTranspose(glm::mat3(matrices.model_view));

    for (unsigned int i = 0; i < lights.size(); i++) {
        auto light = lights[i].light;
        for (auto & uniform : light->uniforms) {
            uniform.set_array_index(i);
            // special uniform names
            if (uniform.get_name() == "enabled") {
                uniform = lights[i].enabled;
            } else if (uniform.get_name() == "position") {
                uniform = matrices.view * glm::vec4(lights[i].position, 1.0f);
            }
        }
    }

    auto & mesh = node.model->mesh;
    render_state->set_vertex_array(mesh.vertex_array);

    auto & effect = node.model->effect;
    for (unsigned int i = 0; i < effect.textures.size(); i++) {
        render_state->set_texture(effect.textures[i], i);
    }

    for (auto technique : effect.techniques) {
        for (auto pass : technique->passes) {
            render_state->set_blend_mode(pass->blend_mode);
            render_state->set_cull_face(pass->cull_face);
            render_state->set_depth_mask(pass->depth_mask);
            render_state->set_depth_test(pass->depth_test);
            render_state->set_program(*pass->program.get());
            pass->program->update(effect.uniforms);
            pass->apply(matrices, lights);
            mesh.draw();
        }
    }
}
