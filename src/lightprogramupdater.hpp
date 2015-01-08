#ifndef LIGHTPROGRAMUPDATER_HPP_INCLUDED
#define LIGHTPROGRAMUPDATER_HPP_INCLUDED

#include "lightvisitor.hpp"
#include "program.hpp"

#include <memory>
#include <string>

namespace gst
{
    class LightProgramUpdater : public LightVisitor {
    public:
        LightProgramUpdater(Program & program, std::string const & prefix);
        virtual void visit(DistantLight & light);
        virtual void visit(HemisphereLight & light);
        virtual void visit(PointLight & light);
        virtual void visit(SpotLight & light);
    private:
        Program program;
        std::string prefix;
    };
}

#endif
