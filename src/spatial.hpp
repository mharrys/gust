#ifndef SPATIAL_HPP_INCLUDED
#define SPATIAL_HPP_INCLUDED

#include "glm.hpp"

namespace gst
{
    // The responsibility of this class is to describe a position and
    // orientation in Euclidean space.
    class Spatial {
    public:
        Spatial();

        // Translate distance on axis in current orientation.
        void translate(float distance, glm::vec3 axis);
        // Translate distance on x-axis in current orientation.
        void translate_x(float distance);
        // Translate distance on y-axis in current orientation.
        void translate_y(float distance);
        // Translate distance on z-axis in current orientation.
        void translate_z(float distance);

        // Rotate with specified number of degrees around specified axis.
        void rotate(float angle_deg, glm::vec3 axis);
        // Rotate with specified number of degrees around x-axis.
        void rotate_x(float angle_deg);
        // Rotate with specified number of degrees around y-axis.
        void rotate_y(float angle_deg);
        // Rotate with specified number of degrees around z-axis.
        void rotate_z(float angle_deg);

        glm::vec3 position;
        glm::vec3 scale;
        glm::quat orientation;

        glm::mat4 local_transform;
        glm::mat4 world_transform;
    };
}

#endif
