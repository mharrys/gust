#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include "attenuation.hpp"
#include "glm.hpp"
#include "uniformarraylocation.hpp"

namespace gst
{
    class LightVisitor;
    class NodeProgramUpdater;

    class Light {
        friend NodeProgramUpdater;
    public:
        Light();
        Light(UniformArrayLocation location);
        virtual ~Light() = default;
        virtual void accept(LightVisitor & visitor);
    private:
        UniformArrayLocation location;
    };
}

#endif
