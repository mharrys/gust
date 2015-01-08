#include "groupnode.hpp"

#include "nodevisitor.hpp"

void gst::GroupNode::accept(NodeVisitor & visitor)
{
    visitor.visit(*this);
    for (auto child : children) {
        child->accept(visitor);
    }
}

void gst::GroupNode::add(std::shared_ptr<Node> node)
{
    children.push_back(node);
    node->parent = shared_from_this();
}

void gst::GroupNode::remove(std::shared_ptr<Node> node)
{
    for (auto i = children.begin(); i != children.end(); i++) {
        if (node == (*i)) {
            node->parent.reset();
            children.erase(i);
            break;
        }
    }
}

