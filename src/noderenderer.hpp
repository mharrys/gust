#ifndef NODERENDERER_HPP_INCLUDED
#define NODERENDERER_HPP_INCLUDED

#include "nodevisitor.hpp"

#include "glm.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class LightNode;
    class RenderState;

    // The responsibility of this class is to render all nodes in a node
    // structure.
    class NodeRenderer : public NodeVisitor {
    public:
        NodeRenderer(
            std::shared_ptr<RenderState> render_state,
            glm::mat4 view,
            glm::mat4 projection,
            std::vector<LightNode> && lights);
        void visit(ModelNode & node) final;
    private:
        std::shared_ptr<RenderState> render_state;
        glm::mat4 view;
        glm::mat4 projection;
        std::vector<LightNode> lights;
    };
}

#endif
