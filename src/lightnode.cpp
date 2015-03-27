#include "lightnode.hpp"

#include "nodevisitor.hpp"

gst::LightNode::LightNode(Light light)
    : light(light)
{
}

void gst::LightNode::accept(NodeVisitor & visitor)
{
    visitor.visit(*this);
}

gst::Light & gst::LightNode::get_light()
{
    return light;
}
