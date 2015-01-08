#ifndef BLINNPHONGSHADING_HPP_INCLUDED
#define BLINNPHONGSHADING_HPP_INCLUDED

#include "materialshading.hpp"
#include "program.hpp"

namespace gst
{
    struct BlinnPhongUniform {
        Uniform ambient;
        Uniform diffuse;
        Uniform specular;
        Uniform emission;
        Uniform shininess;
    };

    class BlinnPhongShading : public MaterialShading {
    public:
        BlinnPhongShading(BlinnPhongUniform uniforms);
        virtual void apply(Program & program, Material & material) override;
    private:
        BlinnPhongUniform uniforms;
    };
}

#endif
