#ifndef SCENE_HPP_INCLUDED
#define SCENE_HPP_INCLUDED

#include "nodetransformupdater.hpp"

#include <memory>
#include <vector>

namespace gst
{
    // The responsibility of this class is to associate a collection of nodes
    // and a camera as a scene.
    class Scene {
    public:
        Scene() = default;
        Scene(std::shared_ptr<CameraNode> eye);
        // Add scene node to root.
        void add(std::shared_ptr<Node> node);
        // Remove scene node from root.
        void remove(std::shared_ptr<Node> node);
        // Traverse scene and perform a node transform update on all nodes.
        void update();
        // Traverse scene and perform a specified operation on all nodes.
        void traverse(NodeVisitor & visitor);
        // Return scene eye/viewpoint.
        CameraNode & get_eye() const;
    private:
        std::shared_ptr<CameraNode> eye;
        std::shared_ptr<GroupNode> root;
        NodeTransformUpdater updater;
    };
}

#endif
