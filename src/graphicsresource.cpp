#include "graphicsresource.hpp"

gst::GraphicsResource::GraphicsResource()
    : name(0),
      dirty(false)
{
}

gst::GraphicsResource::~GraphicsResource()
{
    if (cleanup) {
        cleanup();
    }
}

void gst::GraphicsResource::needs_update()
{
    dirty = true;
}
