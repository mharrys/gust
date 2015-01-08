#ifndef KEYBOARD_HPP_INCLUDED
#define KEYBOARD_HPP_INCLUDED

#include "key.hpp"

#include <vector>

namespace gst
{
    enum class KeyState {
        UP,
        DOWN,
        PRESSED,
        RELEASED
    };

    typedef std::vector<KeyState> Keys;

    class Keyboard {
    public:
        Keyboard();
        void tick();

        Keys keys;
    };
}

#endif
