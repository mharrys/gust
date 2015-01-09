#include "pass.hpp"

#include "effect.hpp"
#include "renderstate.hpp"

gst::Pass::Pass(std::shared_ptr<Program> program)
    : program(program)
{
}

void gst::Pass::prepare(Effect & effect)
{
    effect.program = program;
    effect.bind_callback = [this](RenderState & state) -> void {
        this->run(state);
        this->run();
    };
}

void gst::Pass::run(RenderState &)
{
}

void gst::Pass::run()
{
}
