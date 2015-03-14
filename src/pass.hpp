#ifndef PASS_HPP_INCLUDED
#define PASS_HPP_INCLUDED

#include "blendmode.hpp"
#include "cullface.hpp"
#include "light.hpp"
#include "lightnode.hpp"
#include "viewport.hpp"

#include "glm.hpp"

#include <memory>

namespace gst
{
    class Program;

    struct MatrixState {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 model_view;
        glm::mat4 projection;
        glm::mat3 normal;
    };

    typedef std::vector<LightNode> LightNodes;

    class Pass {
    public:
        Pass();
        Pass(std::shared_ptr<Program> program);
        virtual void apply(MatrixState & matrices, LightNodes & light_nodes);

        BlendMode blend_mode;
        CullFace cull_face;
        bool depth_mask;
        bool depth_test;
        Viewport viewport;
        std::shared_ptr<Program> program;
    };
}

#endif
