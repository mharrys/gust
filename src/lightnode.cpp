#include "lightnode.hpp"

#include "nodevisitor.hpp"

gst::LightNode::LightNode(std::shared_ptr<Light> light)
    : light(light),
      lights_index(0)
{
}

void gst::LightNode::accept(NodeVisitor & visitor)
{
    visitor.visit(*this);
}
