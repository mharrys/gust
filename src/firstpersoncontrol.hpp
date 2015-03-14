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
        FirstPersonControl(bool freelook, float rotation_speed, float movement_speed);
        void update(float dt, Input const & input, Spatial & spatial) final;
    private:
        void rotate(float dt, Input const & input, Spatial & spatial);
        void move(float dt, Input const & input, Spatial & spatial);

        bool freelook;

        float rotation_speed;
        float movement_speed;

        float yaw_angle;
        float pitch_angle;
    };
}

#endif
