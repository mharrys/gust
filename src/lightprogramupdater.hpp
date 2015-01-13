#ifndef LIGHTPROGRAMUPDATER_HPP_INCLUDED
#define LIGHTPROGRAMUPDATER_HPP_INCLUDED

#include "lightvisitor.hpp"

#include <memory>
#include <string>

namespace gst
{
    class Program;

    class LightProgramUpdater : public LightVisitor {
    public:
        LightProgramUpdater(std::shared_ptr<Program> program, std::string const & prefix);
        virtual void visit(DistantLight & light);
        virtual void visit(HemisphereLight & light);
        virtual void visit(PointLight & light);
        virtual void visit(SpotLight & light);
    private:
        std::shared_ptr<Program> program;
        std::string prefix;
    };
}

#endif
