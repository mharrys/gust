#include "basicshading.hpp"

#include "material.hpp"
#include "program.hpp"

void gst::BasicShading::apply(Program & program, Material & material)
{
    program.uniform(program.uniform("material.diffuse"), material.diffuse);
}
