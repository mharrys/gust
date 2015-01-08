#ifndef SPOTLIGHT_HPP_INCLUDED
#define SPOTLIGHT_HPP_INCLUDED

#include "light.hpp"

namespace gst
{
    class SpotLight : public Light {
    public:
        SpotLight();
        SpotLight(UniformArrayLocation location);
        virtual void accept(LightVisitor & visitor);

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        Attenuation attenuation;
        float exponent;
        float cutoff;
    };
}

#endif
