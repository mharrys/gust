#include "noderenderer.hpp"

#include "effect.hpp"
#include "effectnode.hpp"
#include "lightnode.hpp"
#include "mesh.hpp"
#include "model.hpp"
#include "modelnode.hpp"

gst::NodeRenderer::NodeRenderer(
    std::shared_ptr<NodeVisitor> updater,
    std::vector<LightNode> lights)
    : updater(updater),
      lights(std::move(lights))
{
}

void gst::NodeRenderer::visit(EffectNode & node)
{
    node.accept(*updater.get());
    node.effect->quad.draw();
}

void gst::NodeRenderer::visit(ModelNode & node)
{
    node.accept(*updater.get());
    for (unsigned int i = 0; i < lights.size(); i++) {
        lights[i].lights_index = i;
        lights[i].accept(*updater.get());
    }
    node.model->mesh.draw();
}
