#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "clock.hpp"

namespace gst
{
    // The responsibility of this class is to structure callback for running a
    // main event loop.
    class World {
    public:
        virtual ~World() = default;
        // Called once before entering main event loop. Return true if
        // initialization was successful, false otherwise.
        virtual bool create() = 0;
        // Called until window is closed if initialization was successful,
        // 'delta' is seconds since last update and 'elapsed' is time since
        // initialization.
        virtual void update(float delta, float elapsed) = 0;
        // Called once after main event loop exit its control, will be called
        // regardless if initialization was successful or not.
        virtual void destroy() = 0;
    };
}

#endif
