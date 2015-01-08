#include "modelnode.hpp"

#include "model.hpp"
#include "nodevisitor.hpp"

gst::ModelNode::ModelNode(std::shared_ptr<Model> model)
    : model(model)
{
}

void gst::ModelNode::accept(NodeVisitor & visitor)
{
    visitor.visit(*this);
}
