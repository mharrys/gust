#ifndef SPATIAL_HPP_INCLUDED
#define SPATIAL_HPP_INCLUDED

#include "glm.hpp"

namespace gst
{
    class Spatial {
    public:
        Spatial();

        void translate(float distance, glm::vec3 axis);
        void translate_x(float distance);
        void translate_y(float distance);
        void translate_z(float distance);

        void rotate(float angle_deg, glm::vec3 axis);
        void rotate_x(float angle_deg);
        void rotate_y(float angle_deg);
        void rotate_z(float angle_deg);

        glm::vec3 position;
        glm::vec3 scale;
        glm::quat orientation;

        glm::mat4 local_transform;
        glm::mat4 world_transform;
    };
}

#endif
