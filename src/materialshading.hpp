#ifndef MATERIALSHADING_HPP_INCLUDED
#define MATERIALSHADING_HPP_INCLUDED

namespace gst
{
    class Material;

    class MaterialShading {
    public:
        virtual ~MaterialShading() = default;
        virtual void apply(Material & material) = 0;
    };
}

#endif
