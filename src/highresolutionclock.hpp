#ifndef HIGHRESOLUTIONCLOCK_HPP_INCLUDED
#define HIGHRESOLUTIONCLOCK_HPP_INCLUDED

#include "clock.hpp"

#include <chrono>

namespace gst
{
    typedef std::chrono::duration<float> seconds;
    typedef std::chrono::high_resolution_clock::time_point time_point;

    class HighResolutionClock : public Clock {
    public:
        HighResolutionClock();
        float elapsed() const final;
        float delta() final;
    private:
        time_point start;
        time_point last;
    };
}

#endif
