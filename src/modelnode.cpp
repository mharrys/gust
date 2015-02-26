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

const std::shared_ptr<gst::Model> gst::ModelNode::get_model() const
{
    return model;
}
