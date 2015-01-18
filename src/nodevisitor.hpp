#ifndef NODEVISITOR_HPP_INCLUDED
#define NODEVISITOR_HPP_INCLUDED

namespace gst
{
    class CameraNode;
    class GroupNode;
    class LightNode;
    class ModelNode;
    class Node;

    class NodeVisitor {
    public:
        virtual ~NodeVisitor() = default;
        virtual void visit(CameraNode & node);
        virtual void visit(GroupNode & node);
        virtual void visit(LightNode & node);
        virtual void visit(ModelNode & node);
        virtual void visit(Node & node);
    };
}

#endif
