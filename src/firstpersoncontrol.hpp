#ifndef FIRSTPERSONCONTROL_HPP_INCLUDED
#define FIRSTPERSONCONTROL_HPP_INCLUDED

#include "spatialcontrol.hpp"

namespace gst
{
    // The responsibility of this class is to imitate the behavior of
    // first-person camera control.
    class FirstPersonControl : public SpatialControl {
    public:
        FirstPersonControl();
        void update(float dt, Input const & input, Spatial & spatial) override;

        float rotation_speed; // also known as the mouse sensitivity
        float movement_speed;
    private:
        void rotate(float dt, Input const & input, Spatial & spatial);
        void move(float dt, Input const & input, Spatial & spatial);

        float yaw_angle;
        float pitch_angle;
    };
}

#endif
