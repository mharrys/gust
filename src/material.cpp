#include "material.hpp"

#include "materialshading.hpp"

gst::Material::Material(std::shared_ptr<MaterialShading> shading)
    : ambient(0.2f, 0.2f, 0.2f),
      diffuse(0.8f, 0.8f, 0.8f),
      specular(0.0f, 0.0f, 0.0f),
      emission(0.0f, 0.0f, 0.0f),
      shininess(0.0f),
      shading(shading)
{
}
