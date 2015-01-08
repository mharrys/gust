#include "perspectivecamera.hpp"

gst::PerspectiveCamera::PerspectiveCamera()
    : PerspectiveCamera(45.0f, 1.0, 0.1f, 1000.0f)
{
}

gst::PerspectiveCamera::PerspectiveCamera(float fov, float aspect_ratio, float near, float far)
    : Camera(glm::perspective(fov, aspect_ratio, near, far)),
      fov(fov),
      aspect_ratio(aspect_ratio),
      near(near),
      far(far)
{
}

float gst::PerspectiveCamera::get_fov() const
{
    return fov;
}

float gst::PerspectiveCamera::get_aspect_ratio() const
{
    return aspect_ratio;
}

float gst::PerspectiveCamera::get_near() const
{
    return near;
}

float gst::PerspectiveCamera::get_far() const
{
    return far;
}
