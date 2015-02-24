#ifndef MOCKWORLD_HPP_INCLUDED
#define MOCKWORLD_HPP_INCLUDED

#include "world.hpp"

#include "gmock/gmock.h"

namespace gst
{
    class MockWorld : public World {
    public:
        MOCK_METHOD0(create, bool());
        MOCK_METHOD2(update, void(float delta, float elapsed));
        MOCK_METHOD0(destroy, void());
    };
}

#endif
