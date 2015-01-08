#ifndef GLM_HPP_INCLUDED
#define GLM_HPP_INCLUDED

#include "glm/glm.hpp"

#include "glm/gtc/matrix_access.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/quaternion.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glm/gtx/norm.hpp"
#include "glm/gtx/quaternion.hpp"
#include "glm/gtx/string_cast.hpp"

static const float PI = 3.1415926535897932384626433832795;

static const glm::vec3 X_UNIT(1.0f, 0.0f, 0.0f);
static const glm::vec3 Y_UNIT(0.0f, 1.0f, 0.0f);
static const glm::vec3 Z_UNIT(0.0f, 0.0f, 1.0f);

// return unit quaternion representing the rotation from u to v, the vectors u
// and v do not need to be normalized
// http://lolengine.net/blog/2014/02/24/quaternion-from-two-vectors-final
static inline glm::quat rotation_between(glm::vec3 u, glm::vec3 v)
{
    const float norm_u_norm_v = sqrt(glm::dot(u, u) * glm::dot(v, v));
    float real_part = norm_u_norm_v + glm::dot(u, v);

    glm::vec3 w;
    if (real_part < 1.e-6f * norm_u_norm_v) {
        // u and v are approximately opposite, rotate 180 degrees around
        // arbitary orthogonal axis
        real_part = 0.0f;
        if (fabs(u.x) > fabs(u.z)) {
            w = glm::vec3(-u.y, u.x, 0.f);
        } else {
            w = glm::vec3(0.f, -u.z, u.y);
        }
    } else {
        w = glm::cross(u, v);
    }

    return glm::normalize(glm::quat(real_part, w));
}

#endif
