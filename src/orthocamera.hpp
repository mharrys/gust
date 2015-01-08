#ifndef ORTHOCAMERA_HPP_INCLUDED
#define ORTHOCAMERA_HPP_INCLUDED

#include "camera.hpp"

namespace gst
{
    class OrthoCamera : public Camera {
    public:
        OrthoCamera();
        OrthoCamera(float left, float right, float bottom, float top);
        OrthoCamera(float left, float right, float bottom, float top, float near, float far);
        float get_left() const;
        float get_right() const;
        float get_bottom() const;
        float get_top() const;
        float get_near() const;
        float get_far() const;
    private:
        float left;
        float right;
        float bottom;
        float top;
        float near;
        float far;
    };
}

#endif
