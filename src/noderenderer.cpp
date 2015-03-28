#include "noderenderer.hpp"

#include "filter.hpp"
#include "graphicsdevice.hpp"
#include "indexbuffer.hpp"
#include "material.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "modelnode.hpp"
#include "program.hpp"
#include "renderstate.hpp"
#include "shadoweddata.hpp"
#include "vertexbuffer.hpp"

gst::NodeRenderer::NodeRenderer(
    std::shared_ptr<GraphicsDevice> device,
    std::shared_ptr<RenderState> render_state,
    ModelState const & model_state,
    Filter * const filter)
    : device(device),
      render_state(render_state),
      model_state(model_state),
      filter(filter)
{
}

void gst::NodeRenderer::visit(ModelNode & node)
{
    model_state.model = node.world_transform;
    model_state.model_view = model_state.view * model_state.model;
    model_state.normal = glm::inverseTranspose(glm::mat3(model_state.model_view));

    auto & mesh = node.get_mesh();
    auto & material = filter ? filter->get_material() : node.get_material();
    auto & pass = filter ? filter->get_pass() : node.get_pass();
    auto & textures = material.get_textures();

    // set textures at the texture unit in the order they are stored in, the
    // uniforms in material will associate texture unit with a annotation
    for (auto i = 0u; i < textures.size(); i++) {
        if (textures[i]) {
            render_state->set_texture(textures[i], i);
        }
    }

    pass.program->merge_uniforms(material.get_uniforms());
    pass.apply(model_state);

    render_state->set_blend_mode(pass.blend_mode);
    render_state->set_cull_face(pass.cull_face);
    render_state->set_depth_mask(pass.depth_mask);
    render_state->set_depth_test(pass.depth_test);
    render_state->set_program(pass.program);
    render_state->set_vertex_array(mesh.vertex_array);

    if (mesh.index) {
        auto count = mesh.index->get_shadowed_data().get_count();
        device->draw_elements(mesh.mode, count);
    } else {
        auto count = mesh.positions->get_shadowed_data().get_count();
        device->draw_arrays(mesh.mode, 0, count);
    }
}
