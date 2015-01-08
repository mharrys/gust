#ifndef PASS_HPP_INCLUDED
#define PASS_HPP_INCLUDED

#include "program.hpp"

#include <memory>

namespace gst
{
    class Effect;
    class Program;
    class RenderState;

    class Pass {
    public:
        Pass() = default;
        Pass(Program & program);
        virtual ~Pass() = default;
        virtual void prepare(Effect & effect);
        virtual void run(RenderState & state);
        virtual void run();
    protected:
        Program program;
    };
}

#endif
