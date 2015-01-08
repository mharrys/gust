#ifndef WORLD_HPP_INCLUDED
#define WORLD_HPP_INCLUDED

#include "clock.hpp"

namespace gst
{
    class World {
    public:
        virtual ~World() = default;
        virtual bool create() = 0;
        virtual void update(seconds delta, seconds elapsed);
        virtual void destroy();
    };
}

#endif
