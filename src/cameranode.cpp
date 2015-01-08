#include "cameranode.hpp"

#include "camera.hpp"
#include "nodevisitor.hpp"

gst::CameraNode::CameraNode(std::shared_ptr<Camera> camera)
    : camera(camera)
{
}

void gst::CameraNode::accept(NodeVisitor & visitor)
{
    visitor.visit(*this);
}

glm::mat4 gst::CameraNode::get_view() const
{
    return glm::inverse(world_transform);
}

glm::mat4 gst::CameraNode::get_projection() const
{
    return camera->get_projection();
}
