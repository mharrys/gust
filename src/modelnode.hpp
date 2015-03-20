#ifndef MODELNODE_HPP_INCLUDED
#define MODELNODE_HPP_INCLUDED

#include "node.hpp"

namespace gst
{
    class Effect;
    class Mesh;
    class Model;

    // The responsibility of this class is to position a model.
    class ModelNode : public Node {
    public:
        ModelNode(std::shared_ptr<Model> model);
        void accept(NodeVisitor & visitor) final;
        // Return model mesh.
        Mesh & get_mesh() const;
        // Return model effect.
        Effect & get_effect() const;
    private:
        std::shared_ptr<Model> model;
    };
}

#endif
