#ifndef DRAWMODE_HPP_INCLUDED
#define DRAWMODE_HPP_INCLUDED

namespace gst
{
    // Specifies primitives to render.
    enum class DrawMode {
        POINTS,
        LINE_STRIP,
        LINE_LOOP,
        LINES,
        TRIANGLE_STRIP,
        TRIANGLE_FAN,
        TRIANGLES
    };
}

#endif
