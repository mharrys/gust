#ifndef LIGHTNODECOLLECTOR_HPP_INCLUDED
#define LIGHTNODECOLLECTOR_HPP_INCLUDED

#include "lightnode.hpp"
#include "nodevisitor.hpp"

#include <vector>

namespace gst
{
    // The responsibility of this class is to collect all light nodes in a
    // node structure.
    class LightNodeCollector : public NodeVisitor {
    public:
        void visit(LightNode & node) final;
        // Return collected lights.
        std::vector<LightNode> get_light_nodes() const;
    private:
        std::vector<LightNode> light_nodes;
    };
}

#endif
