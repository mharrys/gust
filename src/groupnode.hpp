#ifndef GROUPNODE_HPP_INCLUDED
#define GROUPNODE_HPP_INCLUDED

#include "node.hpp"

#include <memory>
#include <list>

namespace gst
{
    // The responsibility of this class is to group one or more nodes, the
    // collection of nodes may also be group nodes (composite pattern).
    class GroupNode : public Node, public std::enable_shared_from_this<GroupNode> {
    public:
        // Accept node visitor but will not invoke children if this group node
        // is disabled.
        void accept(NodeVisitor & visitor) override;
        // Add child node.
        void add(std::shared_ptr<Node> node);
        // Remove child node.
        void remove(std::shared_ptr<Node> node);
    private:
        std::list<std::shared_ptr<Node>> children;
    };
}

#endif
