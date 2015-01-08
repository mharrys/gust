#include "effectnode.hpp"

#include "effect.hpp"
#include "nodevisitor.hpp"

gst::EffectNode::EffectNode(std::shared_ptr<Effect> effect)
    : effect(effect)
{
}

void gst::EffectNode::accept(NodeVisitor & visitor)
{
    visitor.visit(*this);
}
