#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include "spatial.hpp"

#include <memory>
#include <string>
#include <vector>

namespace gst
{
    class NodeVisitor;

    // The responsibility of this class is to describe a node structure in
    // Euclidean space.
    class Node : public Spatial {
    public:
        Node();
        Node(std::string name);
        virtual ~Node() = default;
        // Handle visitor.
        virtual void accept(NodeVisitor & visitor) = 0;
        // Set owner for this node.
        void set_parent(std::shared_ptr<Node> parent);
        // Return owner for this node, null if no owner.
        std::weak_ptr<Node> get_parent() const;
        // Return name of node.
        std::string get_name() const;
    private:
        std::string name;
        std::weak_ptr<Node> parent;
    };
}

#endif
