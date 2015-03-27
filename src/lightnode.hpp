#ifndef LIGHTNODE_HPP_INCLUDED
#define LIGHTNODE_HPP_INCLUDED

#include "light.hpp"
#include "node.hpp"

namespace gst
{
    // The responsibility of this class is to position a light.
    class LightNode : public Node {
    public:
        LightNode(Light light);
        void accept(NodeVisitor & visitor) final;
        // Return light.
        Light & get_light();
    private:
        Light light;
    };
}

#endif
