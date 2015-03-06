#ifndef NODETRANSFORMUPDATER_HPP_INCLUDED
#define NODETRANSFORMUPDATER_HPP_INCLUDED

#include "nodevisitor.hpp"

namespace gst
{
    // The responsibility of this class is to update the spatial matrices for
    // all nodes in a node structure.
    class NodeTransformUpdater : public NodeVisitor {
    public:
        void visit(CameraNode & node) override;
        void visit(GroupNode & node) override;
        void visit(LightNode & node) override;
        void visit(ModelNode & node) override;
    private:
        void update(Node & node);
        void update_local_transform(Node & node);
        void update_world_transform(Node & node);
    };
}

#endif
