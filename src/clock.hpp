#ifndef CLOCK_HPP_INCLUDED
#define CLOCK_HPP_INCLUDED

#include <chrono>

namespace gst
{
    typedef std::chrono::duration<float> seconds;
    typedef std::chrono::high_resolution_clock::time_point time_point;

    class Clock {
    public:
        Clock();
        seconds elapsed() const;
        seconds delta();
    private:
        time_point start;
        time_point last;
    };
}

#endif
