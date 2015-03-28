#include "modelnode.hpp"

#include "nodevisitor.hpp"

gst::ModelNode::ModelNode(Model model)
    : model(model)
{
}

void gst::ModelNode::accept(NodeVisitor & visitor)
{
    visitor.visit(*this);
}

gst::Mesh & gst::ModelNode::get_mesh()
{
    return model.get_mesh();
}

gst::Material & gst::ModelNode::get_material()
{
    return model.get_material();
}

gst::Pass & gst::ModelNode::get_pass()
{
    return model.get_pass();
}

gst::Model & gst::ModelNode::get_model()
{
    return model;
}
