#ifndef NODERENDERER_HPP_INCLUDED
#define NODERENDERER_HPP_INCLUDED

#include "glm.hpp"
#include "nodevisitor.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class CameraNode;
    class LightNode;
    class RenderState;

    class NodeRenderer : public NodeVisitor {
    public:
        NodeRenderer(
            std::shared_ptr<RenderState> render_state,
            std::shared_ptr<CameraNode> eye,
            std::vector<LightNode> lights);
        void visit(ModelNode & node);
    private:
        std::shared_ptr<RenderState> render_state;
        std::shared_ptr<CameraNode> eye;
        std::vector<LightNode> lights;
    };
}

#endif
