#include "basicshading.hpp"

#include "material.hpp"

gst::BasicShading::BasicShading(std::shared_ptr<Program> program)
    : program(program),
      diffuse(program->uniform("material.diffuse"))
{
}

void gst::BasicShading::apply(Material & material)
{
    program->uniform(diffuse, material.diffuse);
}
