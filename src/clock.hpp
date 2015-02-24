#ifndef CLOCK_HPP_INCLUDED
#define CLOCK_HPP_INCLUDED

namespace gst
{
    // The responsibility of this class is to track the passing of time.
    class Clock {
    public:
        virtual ~Clock() = default;
        // Return time in seconds since class was created.
        virtual float elapsed() const = 0;
        // Return time in seconds since function was last called, clamped at 1
        // second.
        virtual float delta() = 0;
    };
}

#endif
