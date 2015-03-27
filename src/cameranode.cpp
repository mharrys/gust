#include "cameranode.hpp"

#include "camera.hpp"
#include "nodevisitor.hpp"

gst::CameraNode::CameraNode(std::unique_ptr<Camera> camera)
    : camera(std::move(camera))
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

gst::Camera & gst::CameraNode::get_camera()
{
    return *camera;
}
