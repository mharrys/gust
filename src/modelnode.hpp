#ifndef MODELNODE_HPP_INCLUDED
#define MODELNODE_HPP_INCLUDED

#include "node.hpp"

namespace gst
{
    class Model;

    class ModelNode : public Node {
    public:
        ModelNode(std::shared_ptr<Model> model);
        virtual void accept(NodeVisitor & visitor) override;

        std::shared_ptr<Model> model;
    };
}

#endif
