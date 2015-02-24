#include "worldrunner.hpp"

#include "clock.hpp"
#include "window.hpp"
#include "world.hpp"

int gst::WorldRunner::control(World & world, Clock & clock, Window & window) const
{
    if (window.should_close()) {
        return 1;
    }

    if (!world.create()) {
        world.destroy();
        return 1;
    }

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
