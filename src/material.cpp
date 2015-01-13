#include "material.hpp"

#include "materialshading.hpp"

gst::Material::Material(std::shared_ptr<MaterialShading> shading)
    : ambient(0.0f),
      diffuse(0.0f),
      specular(0.0f),
      emission(0.0f),
      shininess(0.0f),
      shading(shading)
{
}
