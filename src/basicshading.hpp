#ifndef BASICSHADING_HPP_INCLUDED
#define BASICSHADING_HPP_INCLUDED

#include "materialshading.hpp"

namespace gst
{
    class BasicShading : public MaterialShading {
    public:
        void apply(Program & program, Material & material) override;
    };
}

#endif
