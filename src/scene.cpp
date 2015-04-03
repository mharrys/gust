#include "scene.hpp"

#include "cameranode.hpp"
#include "groupnode.hpp"
#include "node.hpp"
#include "nodevisitor.hpp"
#include "orthocamera.hpp"
#include "perspectivecamera.hpp"

gst::Scene gst::Scene::create_ortho(OrthoCamera camera)
{
    auto camera_ptr = std::unique_ptr<Camera>(new OrthoCamera(camera));
    auto eye = std::make_shared<CameraNode>(std::move(camera_ptr));
    return Scene(eye);
}

gst::Scene gst::Scene::create_perspective(PerspectiveCamera camera)
{
    auto camera_ptr = std::unique_ptr<Camera>(new PerspectiveCamera(camera));
    auto eye = std::make_shared<CameraNode>(std::move(camera_ptr));
    return Scene(eye);
}

gst::Scene::Scene(std::shared_ptr<CameraNode> eye)
    : eye(eye),
      root(std::make_shared<GroupNode>())
{
}

void gst::Scene::add(std::shared_ptr<Node> node)
{
    root->add(node);
}

void gst::Scene::remove(std::shared_ptr<Node> node)
{
    root->remove(node);
}

void gst::Scene::update()
{
    traverse(updater);
}

void gst::Scene::traverse(NodeVisitor & visitor)
{
    eye->accept(visitor);
    root->accept(visitor);
}

gst::CameraNode & gst::Scene::get_eye()
{
    return *eye;
}
