#include "node.hpp"

#include "nodevisitor.hpp"

gst::Node::Node()
    : Node("unnamed")
{
}

gst::Node::Node(std::string name)
    : name(name)
{
}

void gst::Node::set_parent(std::shared_ptr<Node> parent)
{
    this->parent = parent;
}

std::weak_ptr<gst::Node> gst::Node::get_parent() const
{
    return parent;
}

std::string gst::Node::get_name() const
{
    return name;
}
