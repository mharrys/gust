#include "orthocamera.hpp"

gst::OrthoCamera::OrthoCamera()
    : OrthoCamera(-1.0f, 1.0f, -1.0f, 1.0f)
{
}

gst::OrthoCamera::OrthoCamera(float left, float right, float bottom, float top)
    : OrthoCamera(left, right, bottom, top, -1.0f, 1.0f)
{
}

gst::OrthoCamera::OrthoCamera(float left, float right, float bottom, float top, float near, float far)
    : projection(glm::ortho(left, right, bottom, top, near, far)),
      left(left),
      right(right),
      bottom(bottom),
      top(top),
      near(near),
      far(far)
{
}

glm::mat4 gst::OrthoCamera::get_projection() const
{
    return projection;
}

float gst::OrthoCamera::get_left() const
{
    return left;
}

float gst::OrthoCamera::get_right() const
{
    return right;
}

float gst::OrthoCamera::get_bottom() const
{
    return bottom;
}

float gst::OrthoCamera::get_top() const
{
    return top;
}

float gst::OrthoCamera::get_near() const
{
    return near;
}

float gst::OrthoCamera::get_far() const
{
    return far;
}
