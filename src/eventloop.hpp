#ifndef EVENTLOOP_HPP_INCLUDED
#define EVENTLOOP_HPP_INCLUDED

namespace gst
{
    class Window;
    class World;

    class EventLoop {
    public:
        int control(Window & window, World & world);
    };
}

#endif
