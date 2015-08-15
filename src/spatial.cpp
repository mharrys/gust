#include "spatial.hpp"

gst::Spatial::Spatial()
    : scale(1.0f),
      local_transform(1.0f),
      world_transform(1.0f)
{
}

void gst::Spatial::translate(float distance, glm::vec3 axis)
{
    position += orientation * (axis * distance);
}

void gst::Spatial::translate_x(float distance)
{
    translate(distance, X_UNIT);
}

void gst::Spatial::translate_y(float distance)
{
    translate(distance, Y_UNIT);
}

void gst::Spatial::translate_z(float distance)
{
    translate(distance, Z_UNIT);
}

void gst::Spatial::rotate_x(float angle_deg)
{
    rotate(angle_deg, X_UNIT);
}

void gst::Spatial::rotate_y(float angle_deg)
{
    rotate(angle_deg, Y_UNIT);
}

void gst::Spatial::rotate_z(float angle_deg)
{
    rotate(angle_deg, Z_UNIT);
}

void gst::Spatial::rotate(float angle_deg, glm::vec3 axis)
{
    orientation = glm::rotate(orientation, glm::radians(angle_deg), axis);
}
