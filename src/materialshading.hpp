#ifndef MATERIALSHADING_HPP_INCLUDED
#define MATERIALSHADING_HPP_INCLUDED

namespace gst
{
    class Material;
    class Program;

    class MaterialShading {
    public:
        virtual ~MaterialShading() = default;
        virtual void apply(Program & program, Material & material) = 0;
    };
}

#endif
