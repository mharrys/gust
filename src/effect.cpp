#include "effect.hpp"

gst::Effect::Effect(Mesh & quad, RenderTarget & read, std::shared_ptr<Program> program)
    : quad(quad),
      read(read),
      program(program)
{
}
