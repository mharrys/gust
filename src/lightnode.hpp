#ifndef LIGHTNODE_HPP_INCLUDED
#define LIGHTNODE_HPP_INCLUDED

#include "node.hpp"

namespace gst
{
    class Light;

    class LightNode : public Node {
    public:
        LightNode(std::shared_ptr<Light> light);
        virtual void accept(NodeVisitor & visitor) override;

        std::shared_ptr<Light> light;
        bool enabled;
        unsigned int lights_index;
    };
}

#endif
