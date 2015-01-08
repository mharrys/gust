#ifndef HEMISPHERELIGHT_HPP_INCLUDED
#define HEMISPHERELIGHT_HPP_INCLUDED

#include "light.hpp"

namespace gst
{
    class HemisphereLight : public Light {
    public:
        HemisphereLight();
        HemisphereLight(UniformArrayLocation location);
        virtual void accept(LightVisitor & visitor);

        glm::vec3 upper;
        glm::vec3 lower;
        glm::vec3 direction;
    };
}

#endif
