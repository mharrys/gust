#ifndef NODEPROGRAMUPDATER_HPP_INCLUDED
#define NODEPROGRAMUPDATER_HPP_INCLUDED

#include "glm.hpp"
#include "nodevisitor.hpp"
#include "program.hpp"

#include <memory>

namespace gst
{
    class RenderState;

    class NodeProgramUpdater : public NodeVisitor {
    public:
        NodeProgramUpdater(
            std::shared_ptr<RenderState> render_state,
            glm::mat4 view,
            glm::mat4 projection);
        virtual void visit(EffectNode & node);
        virtual void visit(ModelNode & node);
        virtual void visit(LightNode & node);
    private:
        std::shared_ptr<RenderState> render_state;
        Program program;
        glm::mat4 view;
        glm::mat4 projection;
    };
}

#endif
