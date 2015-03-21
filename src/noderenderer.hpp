#ifndef NODERENDERER_HPP_INCLUDED
#define NODERENDERER_HPP_INCLUDED

#include "effect.hpp"
#include "nodevisitor.hpp"
#include "pass.hpp"

#include "glm.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class GraphicsDevice;
    class RenderState;

    // The responsibility of this class is to render all nodes in a node
    // structure.
    class NodeRenderer : public NodeVisitor {
    public:
        NodeRenderer(
            std::shared_ptr<GraphicsDevice> device,
            std::shared_ptr<RenderState> render_state,
            ModelState && state);
        void visit(ModelNode & node) final;
        // Set effect to be used for all nodes during render.
        void set_effect_override(Effect & effect);
    private:
        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<RenderState> render_state;
        ModelState state;

        Effect effect_override;
        bool use_effect_override;
    };
}

#endif
