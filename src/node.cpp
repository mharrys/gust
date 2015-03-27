#include "node.hpp"

#include "nodevisitor.hpp"

void gst::Node::set_parent(std::shared_ptr<Node> parent)
{
    this->parent = parent;
}

std::weak_ptr<gst::Node> gst::Node::get_parent() const
{
    return parent;
}
