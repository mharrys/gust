#ifndef CAMERANODE_HPP_INCLUDED
#define CAMERANODE_HPP_INCLUDED

#include "node.hpp"

namespace gst
{
    class Camera;

    // The responsibility of this class is to position a camera.
    class CameraNode : public Node {
    public:
        CameraNode(std::shared_ptr<Camera> camera);
        void accept(NodeVisitor & visitor) override;
        // Return camera space.
        glm::mat4 get_view() const;
        // Return camera projection.
        glm::mat4 get_projection() const;
    private:
        std::shared_ptr<Camera> camera;
    };
}

#endif
