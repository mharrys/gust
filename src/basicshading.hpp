#ifndef BASICSHADING_HPP_INCLUDED
#define BASICSHADING_HPP_INCLUDED

#include "materialshading.hpp"
#include "program.hpp"

namespace gst
{
    struct BasicUniform {
        Uniform diffuse;
    };

    class BasicShading : public MaterialShading {
    public:
        BasicShading(BasicUniform uniforms);
        void apply(Program & program, Material & material) override;
    private:
        BasicUniform uniforms;
    };
}

#endif
