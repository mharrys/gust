#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "clock.hpp"

namespace gst
{
    // The responsibility of this class is to structure callback for running a
    // main event loop for a open window.
    class World {
    public:
        virtual ~World() = default;
        // Called once before entering main event loop. Return true if
        // initialization was successful, false otherwise.
        virtual bool create() = 0;
        // Called until window is closed after initialization is successful.
        // The delta parameter represents the time in seconds since the last
        // update and the elapsed parameter represents the time in seconds
        // since create was called.
        virtual void update(float delta, float elapsed) = 0;
        // Called once after main program event loop exit its control, will be
        // called regardless if initialization was successful or not.
        virtual void destroy() = 0;
    };
}

#endif
