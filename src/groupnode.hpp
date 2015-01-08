#ifndef GROUPNODE_HPP_INCLUDED
#define GROUPNODE_HPP_INCLUDED

#include "node.hpp"

#include <memory>
#include <list>

namespace gst
{
    class GroupNode : public Node, public std::enable_shared_from_this<GroupNode> {
    public:
        void accept(NodeVisitor & visitor) override;
        void add(std::shared_ptr<Node> node);
        void remove(std::shared_ptr<Node> node);
    private:
        std::list<std::shared_ptr<Node>> children;
    };
}

#endif
