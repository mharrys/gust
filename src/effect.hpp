#ifndef EFFECT_HPP_INCLUDED
#define EFFECT_HPP_INCLUDED

#include "mesh.hpp"
#include "rendertarget.hpp"
#include "program.hpp"

#include <functional>
#include <memory>

namespace gst
{
    class RenderState;

    class Effect {
    public:
        Effect(Mesh & quad, RenderTarget & read, std::shared_ptr<Program> program);

        Mesh quad;
        RenderTarget read;
        std::shared_ptr<Program> program;
        std::function<void(RenderState &)> bind_callback;
    };
}

#endif
