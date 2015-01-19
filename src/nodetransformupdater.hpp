#ifndef NODETRANSFORMUPDATER_HPP_INCLUDED
#define NODETRANSFORMUPDATER_HPP_INCLUDED

#include "nodevisitor.hpp"

namespace gst
{
    // TODO: update transform only when flagged
    class NodeTransformUpdater : public NodeVisitor {
    public:
        void visit(CameraNode & node);
        void visit(GroupNode & node);
        void visit(LightNode & node);
        void visit(ModelNode & node);
    private:
        void update(Node & node);
        void update_local_transform(Node & node);
        void update_world_transform(Node & node);
    };
}

#endif
