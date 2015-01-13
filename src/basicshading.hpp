#ifndef BASICSHADING_HPP_INCLUDED
#define BASICSHADING_HPP_INCLUDED

#include "materialshading.hpp"
#include "program.hpp"

namespace gst
{
    class BasicShading : public MaterialShading {
    public:
        BasicShading(std::shared_ptr<Program> program);
        void apply(Material & material) override;
    private:
        std::shared_ptr<Program> program;
        Uniform diffuse;
    };
}

#endif
