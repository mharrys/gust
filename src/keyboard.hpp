#ifndef KEYBOARD_HPP_INCLUDED
#define KEYBOARD_HPP_INCLUDED

#include "key.hpp"

#include <vector>

namespace gst
{
    // Keyboard key states. Complete cycle: PRESSED -> DOWN -> RELEASED -> UP.
    enum class KeyState {
        UP,      // Key is inactive.
        DOWN,    // Key is active.
        PRESSED, // Key was just pressed down (one frame).
        RELEASED // Key was just released from its active state (one frame).
    };

    typedef std::vector<KeyState> Keys;

    // The responsibility of this class is to track the state of a keyboard.
    class Keyboard {
    public:
        Keyboard();
        // Advance keyboard state. Keys with state PRESSED will have its state
        // changed to DOWN and keys with state RELEASED will have its state
        // changed to UP.
        void tick();
        // Set key state.
        void set_key_state(Key key, KeyState state);
        // Return key state.
        KeyState get_key_state(Key key) const;
    private:
        Keys keys;
    };
}

#endif
