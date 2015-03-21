#include "mouse.hpp"

gst::Mouse::Mouse()
    : buttons(static_cast<int>(Button::COUNT), ButtonState::UP),
      position(0, 0),
      position_delta(0, 0),
      scroll_delta(0)
{
}

void gst::Mouse::tick()
{
    for (auto i = 0u; i < buttons.size(); i++) {
        ButtonState state = buttons[i];
        if (state == ButtonState::CLICKED || state == ButtonState::DBLCLICKED) {
            buttons[i] = ButtonState::DOWN;
        } else if (state == ButtonState::RELEASED) {
            buttons[i] = ButtonState::UP;
        }
    }
    position_delta.x = 0;
    position_delta.y = 0;
    scroll_delta = 0;
}

void gst::Mouse::set_button_state(Button button, ButtonState state)
{
    buttons[static_cast<int>(button)] = state;
}

void gst::Mouse::set_position(glm::ivec2 position)
{
    this->position = position;
}

void gst::Mouse::add_position_delta(glm::ivec2 delta)
{
    position_delta += delta;
}

void gst::Mouse::add_scroll_delta(int delta)
{
    scroll_delta += delta;
}

gst::ButtonState gst::Mouse::get_button_state(Button button) const
{
    return buttons[static_cast<int>(button)];
}

glm::ivec2 gst::Mouse::get_position() const
{
    return position;
}

glm::ivec2 gst::Mouse::get_position_delta() const
{
    return position_delta;
}

int gst::Mouse::get_scroll_delta() const
{
    return scroll_delta;
}
