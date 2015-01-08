#ifndef POINTLIGHT_HPP_INCLUDED
#define POINTLIGHT_HPP_INCLUDED

#include "light.hpp"

namespace gst
{
    class PointLight : public Light {
    public:
        PointLight();
        PointLight(UniformArrayLocation location);
        virtual void accept(LightVisitor & visitor);

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        Attenuation attenuation;
    };
}

#endif
