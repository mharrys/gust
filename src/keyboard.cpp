#include "keyboard.hpp"

gst::Keyboard::Keyboard()
    : keys(static_cast<int>(Key::COUNT), KeyState::UP)
{
}

void gst::Keyboard::tick()
{
    for (unsigned int i = 0; i < keys.size(); i++) {
        KeyState state = keys[i];
        if (state == KeyState::PRESSED) {
            keys[i] = KeyState::DOWN;
        } else if (state == KeyState::RELEASED) {
            keys[i] = KeyState::UP;
        }
    }
}

void gst::Keyboard::set_key_state(Key key, KeyState state)
{
    keys[static_cast<int>(key)] = state;
}

gst::KeyState gst::Keyboard::get_key_state(Key key) const
{
    return keys[static_cast<int>(key)];
}
