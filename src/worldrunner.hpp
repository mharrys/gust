#ifndef WORLDRUNNER_HPP_INCLUDED
#define WORLDRUNNER_HPP_INCLUDED

namespace gst
{
    class Window;
    class World;

    class WorldRunner {
    public:
        int control(Window & window, World & world);
    };
}

#endif
