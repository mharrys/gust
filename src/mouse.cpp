#include "mouse.hpp"

gst::Mouse::Mouse()
    : buttons(static_cast<int>(Button::COUNT), ButtonState::UP),
      position(0, 0),
      position_rel(0, 0),
      scroll_delta(0)
{
}

void gst::Mouse::tick()
{
    for (unsigned int i = 0; i < buttons.size(); i++) {
        ButtonState state = buttons[i];
        if (state == ButtonState::CLICKED || state == ButtonState::DBLCLICKED) {
            buttons[i] = ButtonState::DOWN;
        } else if (state == ButtonState::RELEASED) {
            buttons[i] = ButtonState::UP;
        }
    }
    scroll_delta = 0;
    position_rel.x = 0;
    position_rel.y = 0;
}
