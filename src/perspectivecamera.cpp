#include "perspectivecamera.hpp"

gst::PerspectiveCamera::PerspectiveCamera()
    : PerspectiveCamera(45.0f, 1.0, 0.1f, 1000.0f)
{
}


gst::PerspectiveCamera::PerspectiveCamera(float fov, Resolution resolution, float near, float far)
    : PerspectiveCamera(fov, resolution.get_width() / static_cast<float>(resolution.get_height()), near, far)
{
}

gst::PerspectiveCamera::PerspectiveCamera(float fov, float aspect_ratio, float near, float far)
    : projection(glm::perspective(fov, aspect_ratio, near, far)),
      fov(fov),
      aspect_ratio(aspect_ratio),
      near(near),
      far(far)
{
}

glm::mat4 gst::PerspectiveCamera::get_projection() const
{
    return projection;
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
