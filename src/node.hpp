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
        virtual void accept(NodeVisitor & visitor);

        std::string name;
        std::weak_ptr<Node> parent;
    };
}

#endif
