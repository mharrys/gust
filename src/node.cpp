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
