#ifndef PASS_HPP_INCLUDED
#define PASS_HPP_INCLUDED

#include "blendmode.hpp"
#include "cullface.hpp"
#include "lightnode.hpp"

#include "glm.hpp"

#include <memory>

namespace gst
{
    class NodeRenderer;
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
        friend NodeRenderer;
    public:
        Pass(std::shared_ptr<Program> program);
        // Setup the program object from the model state.
        virtual void apply(ModelState & state) = 0;
        // Set blend mode.
        void set_blend_mode(BlendMode blend_mode);
        // Set cull face.
        void set_cull_face(CullFace cull_face);
        // Set depth mask.
        void set_depth_mask(bool depth_mask);
        // Set depth test.
        void set_depth_test(bool depth_test);
        // Return blend mode.
        BlendMode get_blend_mode() const;
        // Return cull face.
        CullFace get_cull_face() const;
        // Return depth mask.
        bool get_depth_mask() const;
        // Return depth test.
        bool get_depth_test() const;
    protected:
        std::shared_ptr<Program> program;
        BlendMode blend_mode;
        CullFace cull_face;
        bool depth_mask;
        bool depth_test;
    };
}

#endif
