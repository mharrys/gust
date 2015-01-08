#include "input.hpp"

gst::Input::Input(Keyboard keyboard, Mouse mouse)
    : keyboard(keyboard),
      mouse(mouse)
{
}

bool gst::Input::pressed(Key key) const
{
    return keyboard.keys[static_cast<int>(key)] == KeyState::PRESSED;
}

bool gst::Input::down(Key key) const
{
    return keyboard.keys[static_cast<int>(key)] == KeyState::DOWN;
}

bool gst::Input::released(Key key) const
{
    return keyboard.keys[static_cast<int>(key)] == KeyState::RELEASED;
}

bool gst::Input::up(Key key) const
{
    return keyboard.keys[static_cast<int>(key)] == KeyState::UP;
}

bool gst::Input::clicked(Button button) const
{
    return mouse.buttons[static_cast<int>(button)] == ButtonState::CLICKED;
}

bool gst::Input::dblclicked(Button button) const
{
    return mouse.buttons[static_cast<int>(button)] == ButtonState::DBLCLICKED;
}

bool gst::Input::down(Button button) const
{
    return mouse.buttons[static_cast<int>(button)] == ButtonState::DOWN;
}

bool gst::Input::released(Button button) const
{
    return mouse.buttons[static_cast<int>(button)] == ButtonState::RELEASED;
}

bool gst::Input::up(Button button) const
{
    return mouse.buttons[static_cast<int>(button)] == ButtonState::UP;
}

glm::ivec2 gst::Input::position() const
{
    return mouse.position;
}

glm::ivec2 gst::Input::position_rel() const
{
    return mouse.position_rel;
}

int gst::Input::scroll_delta() const
{
    return mouse.scroll_delta;
}
