#ifndef CAMERANODE_HPP_INCLUDED
#define CAMERANODE_HPP_INCLUDED

#include "node.hpp"

namespace gst
{
    class Camera;

    class CameraNode : public Node {
    public:
        CameraNode(std::shared_ptr<Camera> camera);
        virtual void accept(NodeVisitor & visitor) override;

        glm::mat4 get_view() const;
        glm::mat4 get_projection() const;

        std::shared_ptr<Camera> camera;
    };
}

#endif
