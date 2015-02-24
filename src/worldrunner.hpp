#ifndef WORLDRUNNER_HPP_INCLUDED
#define WORLDRUNNER_HPP_INCLUDED

namespace gst
{
    class Clock;
    class Window;
    class World;

    // The responsibility of this class is to control the main event loop for
    // a world.
    class WorldRunner {
    public:
        // Control main event loop. Return 0 if exit was successful, 1
        // otherwise.
        int control(World & world, Clock & clock, Window & window) const;
    };
}

#endif
