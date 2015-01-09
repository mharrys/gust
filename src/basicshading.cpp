#include "basicshading.hpp"

#include "material.hpp"

gst::BasicShading::BasicShading(BasicUniform uniforms)
    : uniforms(uniforms)
{
}

void gst::BasicShading::apply(Program & program, Material & material)
{
    program.uniform(uniforms.diffuse, material.diffuse);
}
