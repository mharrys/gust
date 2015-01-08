#include "blinnphongshading.hpp"

#include "material.hpp"

gst::BlinnPhongShading::BlinnPhongShading(BlinnPhongUniform uniforms)
    : uniforms(uniforms)
{
}

void gst::BlinnPhongShading::apply(Program & program, Material & material)
{
    program.uniform(uniforms.ambient, material.ambient);
    program.uniform(uniforms.diffuse, material.diffuse);
    program.uniform(uniforms.specular, material.specular);
    program.uniform(uniforms.emission, material.emission);
    program.uniform(uniforms.shininess, material.shininess);
}
