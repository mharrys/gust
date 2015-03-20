#ifndef LIGHTNODE_HPP_INCLUDED
#define LIGHTNODE_HPP_INCLUDED

#include "node.hpp"

namespace gst
{
    class Light;

    // The responsibility of this class is to position a light.
    class LightNode : public Node {
    public:
        LightNode(std::shared_ptr<Light> light);
        void accept(NodeVisitor & visitor) final;
        // Return light.
        Light & get_light() const;
    private:
        std::shared_ptr<Light> light;
    };
}

#endif
