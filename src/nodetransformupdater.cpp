#include "nodetransformupdater.hpp"

#include "cameranode.hpp"
#include "lightnode.hpp"
#include "groupnode.hpp"
#include "modelnode.hpp"

void gst::NodeTransformUpdater::visit(CameraNode & node)
{
    update(node);
}

void gst::NodeTransformUpdater::visit(GroupNode & node)
{
    update(node);
}

void gst::NodeTransformUpdater::visit(LightNode & node)
{
    update(node);
}

void gst::NodeTransformUpdater::visit(ModelNode & node)
{
    update(node);
}

void gst::NodeTransformUpdater::update(Node & node)
{
    update_local_transform(node);
    update_world_transform(node);
}

void gst::NodeTransformUpdater::update_local_transform(Node & node)
{
    glm::mat4 T = glm::translate(glm::mat4(1.0f), node.position);
    glm::mat4 R = glm::toMat4(node.orientation);
    glm::mat4 S = glm::scale(glm::mat4(1.0f), node.scale);
    node.local_transform = T * R * S;
}

void gst::NodeTransformUpdater::update_world_transform(Node & node)
{
    if (auto parent = node.get_parent().lock()) {
        node.world_transform = parent->world_transform * node.local_transform;
    } else {
        node.world_transform = node.local_transform;
    }
}
