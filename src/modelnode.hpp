#ifndef MODELNODE_HPP_INCLUDED
#define MODELNODE_HPP_INCLUDED

#include "node.hpp"

namespace gst
{
    class Model;

    // The responsibility of this class is to position a model.
    class ModelNode : public Node {
    public:
        ModelNode(std::shared_ptr<Model> model);
        void accept(NodeVisitor & visitor) final;
        // Return model.
        const std::shared_ptr<Model> get_model() const;
    private:
        std::shared_ptr<Model> model;
    };
}

#endif
