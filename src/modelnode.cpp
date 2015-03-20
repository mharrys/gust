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

gst::Mesh & gst::ModelNode::get_mesh() const
{
    return model->get_mesh();
}

gst::Effect & gst::ModelNode::get_effect() const
{
    return model->get_effect();
}
