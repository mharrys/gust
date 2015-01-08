#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "nodetransformupdater.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Camera;
    class CameraNode;
    class GroupNode;
    class NodeVisitor;

    class Scene {
    public:
        Scene() = default;
        Scene(std::shared_ptr<Camera> camera);

        void add(std::shared_ptr<Node> node);
        void remove(std::shared_ptr<Node> node);

        void update();
        void traverse(NodeVisitor & visitor);

        std::shared_ptr<CameraNode> eye;
    private:
        std::shared_ptr<GroupNode> root;
        NodeTransformUpdater updater;
    };
}

#endif
