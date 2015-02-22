#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include "glm.hpp"

namespace gst
{
    // The responsibility of this class is to describe a camera lens with a
    // projection matrix.
    class Camera {
    public:
        virtual ~Camera() = default;
        // Return camera projection.
        virtual glm::mat4 get_projection() const = 0;
    };
}

#endif
