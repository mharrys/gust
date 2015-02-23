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
        void accept(NodeVisitor & visitor) override;
        // Return light.
        const std::shared_ptr<Light> get_light() const;
    private:
        std::shared_ptr<Light> light;
    };
}

#endif
