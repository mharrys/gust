#ifndef NODERENDERER_HPP_INCLUDED
#define NODERENDERER_HPP_INCLUDED

#include "nodevisitor.hpp"
#include "pass.hpp"

#include "glm.hpp"

namespace gst
{
    class GraphicsDevice;
    class Material;
    class RenderState;

    // The responsibility of this class is to render all nodes in a node
    // structure.
    class NodeRenderer : public NodeVisitor {
    public:
        // Construct node renderer. It is expected that model state has the
        // view, projection and light nodes set from a scene. The material
        // override is optional, will be used if not null.
        NodeRenderer(
            std::shared_ptr<GraphicsDevice> device,
            std::shared_ptr<RenderState> render_state,
            ModelState const & model_state,
            Material * const material_override);
        void visit(ModelNode & node) final;
    private:
        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<RenderState> render_state;
        ModelState model_state;
        Material * const material_override;
    };
}

#endif
