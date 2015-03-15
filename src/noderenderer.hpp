#ifndef NODERENDERER_HPP_INCLUDED
#define NODERENDERER_HPP_INCLUDED

#include "nodevisitor.hpp"
#include "pass.hpp"

#include "glm.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class RenderState;

    // The responsibility of this class is to render all nodes in a node
    // structure.
    class NodeRenderer : public NodeVisitor {
    public:
        NodeRenderer(
            std::shared_ptr<RenderState> render_state,
            ModelState && state);
        void visit(ModelNode & node) final;
    private:
        std::shared_ptr<RenderState> render_state;
        ModelState state;
    };
}

#endif
