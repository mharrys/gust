#ifndef ORTHOCAMERA_HPP_INCLUDED
#define ORTHOCAMERA_HPP_INCLUDED

#include "camera.hpp"

namespace gst
{
    // The responsibility of this class is to describe a camera with
    // a orthographic projection.
    class OrthoCamera : public Camera {
    public:
        OrthoCamera();
        OrthoCamera(float left, float right, float bottom, float top);
        OrthoCamera(float left, float right, float bottom, float top, float near, float far);
        glm::mat4 get_projection() const override;
        // Return coordinate for left vertical clipping plane.
        float get_left() const;
        // Return coordinate for right vertical clipping plane.
        float get_right() const;
        // Return coordinate for bottom horizontal clipping plane.
        float get_bottom() const;
        // Return coordinate for top horizontal clipping plane.
        float get_top() const;
        // Return distance to near clipping plane.
        float get_near() const;
        // Return distance to far clipping plane.
        float get_far() const;
    private:
        glm::mat4 projection;
        float left;
        float right;
        float bottom;
        float top;
        float near;
        float far;
    };
}

#endif
