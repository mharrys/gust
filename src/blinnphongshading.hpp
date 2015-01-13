#ifndef BLINNPHONGSHADING_HPP_INCLUDED
#define BLINNPHONGSHADING_HPP_INCLUDED

#include "materialshading.hpp"

namespace gst
{
    class BlinnPhongShading : public MaterialShading {
    public:
        void apply(Program & program, Material & material) override;
    };
}

#endif
