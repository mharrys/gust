#ifndef CAMERA_HPP_INCLUDED
#define CAMERA_HPP_INCLUDED

#include "glm.hpp"

namespace gst
{
    class Camera {
    public:
        Camera() = default;
        Camera(glm::mat4 projection);
        glm::mat4 get_projection() const;
    private:
        glm::mat4 projection;
    };
}

#endif
