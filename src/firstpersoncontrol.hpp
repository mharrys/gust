#ifndef FIRSTPERSONCONTROL_HPP_INCLUDED
#define FIRSTPERSONCONTROL_HPP_INCLUDED

#include "clock.hpp"

namespace gst
{
    class Input;
    class Spatial;

    class FirstPersonControl {
    public:
        FirstPersonControl();
        void update(float dt, Input const & input, Spatial & spatial);

        float rotation_speed;
        float movement_speed;
    private:
        void rotate(float dt, Input const & input, Spatial & spatial);
        void move(float dt, Input const & input, Spatial & spatial);

        float yaw_angle;
        float pitch_angle;
    };
}

#endif
