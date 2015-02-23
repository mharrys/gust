#ifndef CULLFACE_HPP_INCLUDED
#define CULLFACE_HPP_INCLUDED

namespace gst
{
    // Specifies if front- and/or back-facing facets can be culled.
    enum class CullFace {
        NONE,           // Face culling disabled.
        FRONT,          // Front faces can be culled.
        BACK,           // Back faces can be culled.
        FRONT_AND_BACK  // Front and back faces can be culled.
    };
}

#endif
