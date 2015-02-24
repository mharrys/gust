#ifndef WORLDRUNNER_HPP_INCLUDED
#define WORLDRUNNER_HPP_INCLUDED

namespace gst
{
    class Clock;
    class Window;
    class World;

    class WorldRunner {
    public:
        int control(World & world, Clock & clock, Window & window) const;
    };
}

#endif
