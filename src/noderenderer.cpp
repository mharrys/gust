#include "noderenderer.hpp"

#include "annotationarray.hpp"
#include "camera.hpp"
#include "cameranode.hpp"
#include "effect.hpp"
#include "lightnode.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "modelnode.hpp"
#include "pass.hpp"
#include "program.hpp"
#include "renderstate.hpp"
#include "shadoweddata.hpp"
#include "uniformmap.hpp"

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
    MatrixState matrices;
    matrices.model = node.world_transform;
    matrices.view = eye->get_view();
    matrices.model_view = matrices.view * matrices.model;
    matrices.projection = eye->get_projection();
    matrices.normal = glm::inverseTranspose(glm::mat3(matrices.model_view));

    for (unsigned int i = 0; i < lights.size(); i++) {
        auto light = lights[i].get_light();
        // special uniforms
        auto uniforms = light->get_uniforms();
        uniforms->get_uniform("enabled") = light->get_enabled();
        uniforms->get_uniform("position") = matrices.view * glm::vec4(lights[i].position, 1.0f);
        // special case if annotation array
        if (auto formatter = std::dynamic_pointer_cast<AnnotationArray>(uniforms->get_formatter())) {
            formatter->set_current_index(i);
        }
    }

    auto model = node.get_model();
    auto & mesh = model->mesh;
    auto & effect = model->effect;
    auto pass = effect.pass;

    render_state->set_vertex_array(mesh.vertex_array);

    for (unsigned int i = 0; i < effect.textures.size(); i++) {
        render_state->set_texture(effect.textures[i], i);
    }

    if (effect.uniforms) {
        pass->program->set_uniforms(effect.uniforms);
    }
    pass->apply(matrices, lights);

    render_state->set_blend_mode(pass->blend_mode);
    render_state->set_cull_face(pass->cull_face);
    render_state->set_depth_mask(pass->depth_mask);
    render_state->set_depth_test(pass->depth_test);
    render_state->set_viewport(pass->viewport);
    render_state->set_program(pass->program);

    mesh.draw();
}
