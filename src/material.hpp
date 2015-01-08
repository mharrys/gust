#ifndef MATERIAL_HPP_INCLUDED
#define MATERIAL_HPP_INCLUDED

#include "glm.hpp"

#include <memory>

namespace gst
{
    class MaterialShading;
    class NodeProgramUpdater;

    class Material {
        friend NodeProgramUpdater;
    public:
        Material(std::shared_ptr<MaterialShading> shading);

        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 emission;
        float shininess;
    private:
        std::shared_ptr<MaterialShading> shading;
    };
}

#endif
