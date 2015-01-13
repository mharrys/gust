#ifndef BLINNPHONGSHADING_HPP_INCLUDED
#define BLINNPHONGSHADING_HPP_INCLUDED

#include "materialshading.hpp"
#include "program.hpp"

namespace gst
{
    class BlinnPhongShading : public MaterialShading {
    public:
        BlinnPhongShading(std::shared_ptr<Program> program);
        void apply(Material & material) override;
    private:
        std::shared_ptr<Program> program;
        Uniform ambient;
        Uniform diffuse;
        Uniform specular;
        Uniform emission;
        Uniform shininess;
    };
}

#endif
