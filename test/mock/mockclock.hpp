#ifndef MOCKCLOCK_HPP_INCLUDED
#define MOCKCLOCK_HPP_INCLUDED

#include "clock.hpp"

#include "gmock/gmock.h"

namespace gst
{
    class MockClock : public Clock {
    public:
        MOCK_CONST_METHOD0(elapsed, float());
        MOCK_METHOD0(delta, float());
    };
}

#endif
