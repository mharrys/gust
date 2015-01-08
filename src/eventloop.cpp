#include "eventloop.hpp"

#include "clock.hpp"
#include "window.hpp"
#include "world.hpp"

int gst::EventLoop::control(Window & window, World & world)
{
    if (window.should_close() || !world.create()) {
        return 1;
    }

    Clock clock;

    while (!window.should_close()) {
        window.poll();

        auto dt = clock.delta();
        auto elapsed = clock.elapsed();
        world.update(dt, elapsed);

        window.swap();
    }

    world.destroy();

    return 0;
}
