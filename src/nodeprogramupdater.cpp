#include "nodeprogramupdater.hpp"

#include "effect.hpp"
#include "effectnode.hpp"
#include "light.hpp"
#include "lightnode.hpp"
#include "lightprogramupdater.hpp"
#include "model.hpp"
#include "modelnode.hpp"
#include "material.hpp"
#include "materialshading.hpp"
#include "renderstate.hpp"
#include "surface.hpp"

#include <string>

gst::NodeProgramUpdater::NodeProgramUpdater(
    std::shared_ptr<RenderState> render_state,
    glm::mat4 view,
    glm::mat4 projection)
    : render_state(render_state),
      view(view),
      projection(projection)
{
}

void gst::NodeProgramUpdater::visit(EffectNode & node)
{
    auto & effect = *node.effect.get();

    program = effect.program;
    render_state->set_blend_mode(BlendMode::NONE);
    render_state->set_cull_face(CullFace::BACK);
    render_state->set_depth_mask(true);
    render_state->set_depth_test(false);
    render_state->set_program(program);
    render_state->set_vertex_array(effect.quad.vertex_array);

    render_state->set_texture(effect.read, 0);
    program.uniform(program.uniform("read"), 0);

    auto size = effect.read.get_size();
    auto resolution = glm::vec2(size.get_width(), size.get_height());
    program.uniform(program.uniform("resolution"), resolution);
    program.uniform(program.uniform("mvp"), projection * view * node.world_transform);

    if (effect.bind_callback) {
        effect.bind_callback(*render_state.get());
    }
}

void gst::NodeProgramUpdater::visit(ModelNode & node)
{
    auto & surface = node.model->surface;
    auto & mesh = node.model->mesh;

    program = surface.program;
    render_state->set_blend_mode(surface.blend_mode);
    render_state->set_cull_face(surface.cull_face);
    render_state->set_depth_mask(surface.depth_mask);
    render_state->set_depth_test(surface.depth_test);
    render_state->set_program(program);
    render_state->set_vertex_array(mesh.vertex_array);

    program.uniform(program.uniform("opacity"), surface.opacity);

    if (surface.color_map) {
        render_state->set_texture(surface.color_map, 0);
        program.uniform(program.uniform("color_map"), 0);
    }

    if (surface.normal_map) {
        render_state->set_texture(surface.normal_map, 1);
        program.uniform(program.uniform("normal_map"), 1);
    }

    surface.material.shading->apply(program, surface.material);

    glm::mat4 m = node.world_transform;
    glm::mat4 mv = view * m;
    glm::mat4 mvp = projection * mv;
    glm::mat3 nm = glm::inverseTranspose(glm::mat3(mv));

    program.uniform(program.uniform("mv"), mv);
    program.uniform(program.uniform("mvp"), mvp);
    program.uniform(program.uniform("nm"), nm);
}

void gst::NodeProgramUpdater::visit(LightNode & node)
{
    const std::string prefix = node.light->location.prefix(node.lights_index);

    glm::vec4 light_position_es = view * glm::vec4(node.position, 1.0f);
    program.uniform(program.uniform(prefix + "enabled"), node.enabled);
    program.uniform(program.uniform(prefix + "position"), light_position_es);

    auto updater = LightProgramUpdater(program, prefix);
    node.light->accept(updater);
}
