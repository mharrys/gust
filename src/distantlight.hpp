#ifndef DISTANTLIGHT_HPP_INCLUDED
#define DISTANTLIGHT_HPP_INCLUDED

#include "light.hpp"

namespace gst
{
    class DistantLight : public Light {
    public:
        DistantLight();
        DistantLight(UniformArrayLocation location);
        virtual void accept(LightVisitor & visitor);

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 direction;
    };
}

#endif
