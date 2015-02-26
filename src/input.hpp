#ifndef INPUT_HPP_INCLUDED
#define INPUT_HPP_INCLUDED

#include "keyboard.hpp"
#include "mouse.hpp"

namespace gst
{
    // The responsibility of this class is to query the current state of a
    // keyboard and a mouse.
    class Input {
    public:
        Input(Keyboard keyboard, Mouse mouse);
        // Return true if keyboard key is pressed, false otherwise.
        bool pressed(Key key) const;
        // Return true if keyboard key is down, false otherwise.
        bool down(Key key) const;
        // Return true if keyboard key is released, false otherwise.
        bool released(Key key) const;
        // Return true if keyboard key is up, false otherwise.
        bool up(Key key) const;
        // Return true if mouse button is clicked, false otherwise.
        bool clicked(Button button) const;
        // Return true if mouse button is double-clicked, false otherwise.
        bool dblclicked(Button button) const;
        // Return true if mouse button is down, false otherwise.
        bool down(Button button) const;
        // Return true if mouse button is released, false otherwise.
        bool released(Button button) const;
        // Return true if mouse button is up, false otherwise.
        bool up(Button button) const;
        // Return mouse pointer position.
        glm::ivec2 position() const;
        // Return change in mouse pointer position.
        glm::ivec2 position_delta() const;
        // Return change in scrolling.
        int scroll_delta() const;
    private:
        Keyboard keyboard;
        Mouse mouse;
    };
}

#endif
