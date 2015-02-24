#ifndef MOCKWINDOW_HPP_INCLUDED
#define MOCKWINDOW_HPP_INCLUDED

#include "input.hpp"
#include "resolution.hpp"
#include "window.hpp"

#include "gmock/gmock.h"

namespace gst
{
    class MockWindow : public Window {
    public:
        MOCK_CONST_METHOD0(should_close, bool());
        MOCK_METHOD0(poll, void());
        MOCK_METHOD0(swap, void());
        MOCK_METHOD1(set_pointer_lock, void(bool pointer_lock));
        MOCK_CONST_METHOD0(get_pointer_lock, bool());
        MOCK_CONST_METHOD0(get_input, Input());
        MOCK_CONST_METHOD0(get_size, Resolution());
    };
}

#endif
