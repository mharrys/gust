#ifndef PERSPECTIVECAMERA_HPP_INCLUDED
#define PERSPECTIVECAMERA_HPP_INCLUDED

#include "camera.hpp"
#include "resolution.hpp"

namespace gst
{
    // The responsibility of this class is to describe a camera with
    // a perspective projection.
    class PerspectiveCamera : public Camera {
    public:
        PerspectiveCamera();
        PerspectiveCamera(float fov, Resolution resolution, float near, float far);
        PerspectiveCamera(float fov, float aspect_ratio, float near, float far);
        glm::mat4 get_projection() const override;
        // Return field of view.
        float get_fov() const;
        // Return aspect ratio.
        float get_aspect_ratio() const;
        // Return distance to near clipping plane.
        float get_near() const;
        // Return distance to far clipping plane.
        float get_far() const;
    private:
        glm::mat4 projection;
        float fov;
        float aspect_ratio;
        float near;
        float far;
    };
}

#endif
