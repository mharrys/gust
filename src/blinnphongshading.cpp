#include "blinnphongshading.hpp"

#include "material.hpp"

gst::BlinnPhongShading::BlinnPhongShading(std::shared_ptr<Program> program)
    : program(program),
      ambient(program->uniform("material.ambient")),
      diffuse(program->uniform("material.diffuse")),
      specular(program->uniform("material.specular")),
      emission(program->uniform("material.emission")),
      shininess(program->uniform("material.shininess"))
{
}

void gst::BlinnPhongShading::apply(Material & material)
{
    program->uniform(ambient, material.ambient);
    program->uniform(diffuse, material.diffuse);
    program->uniform(specular, material.specular);
    program->uniform(emission, material.emission);
    program->uniform(shininess, material.shininess);
}
