#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

#include "keyboard.hpp"
#include "mouse.hpp"

namespace gst
{
    class Input {
    public:
        Input() = default;
        Input(Keyboard keyboard, Mouse mouse);

        bool pressed(Key key) const;
        bool down(Key key) const;
        bool released(Key key) const;
        bool up(Key key) const;

        bool clicked(Button button) const;
        bool dblclicked(Button button) const;
        bool down(Button button) const;
        bool released(Button button) const;
        bool up(Button button) const;

        glm::ivec2 position() const;
        glm::ivec2 position_rel() const;
        int scroll_delta() const;
    private:
        Keyboard keyboard;
        Mouse mouse;
    };
}

#endif
