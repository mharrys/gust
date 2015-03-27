#ifndef MODELNODE_HPP_INCLUDED
#define MODELNODE_HPP_INCLUDED

#include "node.hpp"

namespace gst
{
    class Material;
    class Mesh;
    class Model;

    // The responsibility of this class is to position a model.
    class ModelNode : public Node {
    public:
        ModelNode(std::shared_ptr<Model> model);
        void accept(NodeVisitor & visitor) final;
        // Return model mesh.
        Mesh & get_mesh() const;
        // Return model material.
        Material & get_material() const;
    private:
        std::shared_ptr<Model> model;
    };
}

#endif
