#ifndef SPATIALCONTROL_HPP_INCLUDED
#define SPATIALCONTROL_HPP_INCLUDED

namespace gst
{
    class Input;
    class Spatial;

    // The responsibility of this class is to manipulate a spatial object from
    // a input state.
    class SpatialControl {
    public:
        // Update spatial object from current input state.
        virtual void update(float dt, Input const & input, Spatial & spatial) = 0;
    };
}

#endif
