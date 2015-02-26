#include "input.hpp"

gst::Input::Input(Keyboard keyboard, Mouse mouse)
    : keyboard(keyboard),
      mouse(mouse)
{
}

bool gst::Input::pressed(Key key) const
{
    return keyboard.get_key_state(key) == KeyState::PRESSED;
}

bool gst::Input::down(Key key) const
{
    return keyboard.get_key_state(key) == KeyState::DOWN;
}

bool gst::Input::released(Key key) const
{
    return keyboard.get_key_state(key) == KeyState::RELEASED;
}

bool gst::Input::up(Key key) const
{
    return keyboard.get_key_state(key) == KeyState::UP;
}

bool gst::Input::clicked(Button button) const
{
    return mouse.get_button_state(button) == ButtonState::CLICKED;
}

bool gst::Input::dblclicked(Button button) const
{
    return mouse.get_button_state(button) == ButtonState::DBLCLICKED;
}

bool gst::Input::down(Button button) const
{
    return mouse.get_button_state(button) == ButtonState::DOWN;
}

bool gst::Input::released(Button button) const
{
    return mouse.get_button_state(button) == ButtonState::RELEASED;
}

bool gst::Input::up(Button button) const
{
    return mouse.get_button_state(button) == ButtonState::UP;
}

glm::ivec2 gst::Input::position() const
{
    return mouse.get_position();
}

glm::ivec2 gst::Input::position_delta() const
{
    return mouse.get_position_delta();
}

int gst::Input::scroll_delta() const
{
    return mouse.get_scroll_delta();
}
