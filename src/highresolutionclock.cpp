#include "highresolutionclock.hpp"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;

gst::HighResolutionClock::HighResolutionClock()
    : start(high_resolution_clock::now()),
      last(start)
{
}

float gst::HighResolutionClock::elapsed() const
{
    auto current = high_resolution_clock::now();
    auto elapsed = current - start;

    return duration_cast<seconds>(elapsed).count();
}

float gst::HighResolutionClock::delta()
{
    auto current = high_resolution_clock::now();
    auto delta = current - last;
    last = current;

    // prevent unmanageable delta values
    auto max_delta = seconds(1.0f);
    if (delta > max_delta) {
        return max_delta.count();
    }

    return duration_cast<seconds>(delta).count();
}
