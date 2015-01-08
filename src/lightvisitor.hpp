#ifndef LIGHTVISITOR_HPP_INCLUDED
#define LIGHTVISITOR_HPP_INCLUDED

namespace gst
{
    class Light;
    class DistantLight;
    class HemisphereLight;
    class PointLight;
    class PointLight;
    class SpotLight;

    class LightVisitor {
    public:
        virtual ~LightVisitor() = default;
        virtual void visit(Light & light);
        virtual void visit(DistantLight & light);
        virtual void visit(HemisphereLight & light);
        virtual void visit(PointLight & light);
        virtual void visit(SpotLight & light);
    };
}

#endif
