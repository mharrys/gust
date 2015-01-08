#ifndef EFFECTNODE_HPP_INCLUDED
#define EFFECTNODE_HPP_INCLUDED

#include "node.hpp"

namespace gst
{
    class Effect;

    class EffectNode : public Node {
    public:
        EffectNode(std::shared_ptr<Effect> effect);
        virtual void accept(NodeVisitor & visitor) override;

        std::shared_ptr<Effect> effect;
    };
}

#endif
