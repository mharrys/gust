#ifndef PERSPECTIVECAMERA_HPP_INCLUDED
#define PERSPECTIVECAMERA_HPP_INCLUDED

#include "camera.hpp"
#include "resolution.hpp"

namespace gst
{
    class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera();
        PerspectiveCamera(float fov, Resolution resolution, float near, float far);
        PerspectiveCamera(float fov, float aspect_ratio, float near, float far);
        float get_fov() const;
        float get_aspect_ratio() const;
        float get_near() const;
        float get_far() const;
    private:
        float fov;
        float aspect_ratio;
        float near;
        float far;
    };
}

#endif
