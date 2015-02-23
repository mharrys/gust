#ifndef NODEVISITOR_HPP_INCLUDED
#define NODEVISITOR_HPP_INCLUDED

namespace gst
{
    class CameraNode;
    class GroupNode;
    class LightNode;
    class ModelNode;
    class Node;

    // The responsibility of this class is perform operations on a node
    // structure (visitor pattern).
    class NodeVisitor {
    public:
        virtual ~NodeVisitor() = default;
        // Visit a camera node.
        virtual void visit(CameraNode & node);
        // Visit a group node.
        virtual void visit(GroupNode & node);
        // Visit a light node.
        virtual void visit(LightNode & node);
        // Visit a model node.
        virtual void visit(ModelNode & node);
        // Visit a abstract node.
        virtual void visit(Node & node);
    };
}

#endif
