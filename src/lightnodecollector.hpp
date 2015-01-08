#ifndef LIGHTNODECOLLECTOR_HPP_INCLUDED
#define LIGHTNODECOLLECTOR_HPP_INCLUDED

#include "lightnode.hpp"
#include "nodevisitor.hpp"

#include <vector>

namespace gst
{
    class LightNodeCollector : public NodeVisitor {
    public:
        void visit(LightNode & node);

        std::vector<LightNode> lights;
    };
}

#endif
