#include "effect.hpp"

gst::Effect::Effect(Mesh & quad, RenderTarget & read, Program & program)
    : quad(quad),
      read(read),
      program(program)
{
}
