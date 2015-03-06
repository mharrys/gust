#ifndef NODE_HPP_INCLUDED
#define NODE_HPP_INCLUDED

#include "spatial.hpp"

#include <memory>
#include <string>
#include <vector>

namespace gst
{
    class NodeVisitor;

    class Node : public Spatial {
    public:
        Node();
        Node(std::string name);
        virtual ~Node() = default;
        virtual void accept(NodeVisitor & visitor);

        std::weak_ptr<Node> parent;

        std::string name;
    };
}

#endif
