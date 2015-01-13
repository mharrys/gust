#include "blinnphongshading.hpp"

#include "material.hpp"
#include "program.hpp"

void gst::BlinnPhongShading::apply(Program & program, Material & material)
{
    program.uniform(program.uniform("material.ambient"), material.ambient);
    program.uniform(program.uniform("material.diffuse"), material.diffuse);
    program.uniform(program.uniform("material.specular"), material.specular);
    program.uniform(program.uniform("material.emission"), material.emission);
    program.uniform(program.uniform("material.shininess"), material.shininess);
}
