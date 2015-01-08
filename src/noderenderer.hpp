#ifndef NODERENDERER_HPP_INCLUDED
#define NODERENDERER_HPP_INCLUDED

#include "glm.hpp"
#include "nodevisitor.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class LightNode;

    class NodeRenderer : public NodeVisitor {
    public:
        NodeRenderer(
            std::shared_ptr<NodeVisitor> updater,
            std::vector<LightNode> lights);
        void visit(EffectNode & node);
        void visit(ModelNode & node);
    private:
        std::shared_ptr<NodeVisitor> updater;
        std::vector<LightNode> lights;
    };
}

#endif
