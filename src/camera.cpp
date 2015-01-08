#include "camera.hpp"

gst::Camera::Camera(glm::mat4 projection)
    : projection(projection)
{
}

glm::mat4 gst::Camera::get_projection() const
{
    return projection;
}
