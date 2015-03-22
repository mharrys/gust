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

    // Describes model properties during the render stage.
    struct ModelState {
        glm::mat4 model;
        glm::mat4 view;
        glm::mat4 model_view;
        glm::mat4 projection;
        glm::mat3 normal;
        std::vector<LightNode> light_nodes;
    };

    // The responsibility of this class is to setup a program object from a
    // model state in a specialized way.
    class Pass {
    public:
        Pass();
        Pass(std::shared_ptr<Program> program);
        // Setup the program object from the model state.
        virtual void apply(ModelState const & state) = 0;

        BlendMode blend_mode;
        CullFace cull_face;
        bool depth_mask;
        bool depth_test;
        Viewport viewport;
        std::shared_ptr<Program> program;
    };
}

#endif
