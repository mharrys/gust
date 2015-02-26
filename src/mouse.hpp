#ifndef MOUSE_HPP_INCLUDED
#define MOUSE_HPP_INCLUDED

#include "button.hpp"
#include "glm.hpp"

#include <vector>

namespace gst
{
    // Mouse button states. Complete cycle: (DBL)CLICKED -> DOWN -> RELEASED -> UP.
    enum class ButtonState {
        UP,         // Button is inactive.
        DOWN,       // Button is active.
        CLICKED,    // Button was just clicked (one frame).
        DBLCLICKED, // Button was just double clicked (one frame).
        RELEASED    // Button was just released from its active state (one frame).
    };

    typedef std::vector<ButtonState> Buttons;

    // The responsibility of this class is to track the state of a mouse.
    class Mouse {
    public:
        Mouse();
        // Advance mouse state. Buttons with state CLICKED or DBLCLICKED will
        // have its state changed to DOWN and buttons with state RELEASED will
        // have its state changed to UP. Change in scrolling and position will
        // be reset to zero.
        void tick();
        // Set button state.
        void set_button_state(Button button, ButtonState state);
        // Set pointer position.
        void set_position(glm::ivec2 position);
        // Increase relative pointer position.
        void add_position_delta(glm::ivec2 delta);
        // Increase change in scrolling.
        void add_scroll_delta(int delta);
        // Get button state.
        ButtonState get_button_state(Button button) const;
        // Get pointer position.
        glm::ivec2 get_position() const;
        // Get change in pointer position.
        glm::ivec2 get_position_delta() const;
        // Get change in scrolling.
        int get_scroll_delta() const;
    private:
        Buttons buttons;
        glm::ivec2 position;
        glm::ivec2 position_delta;
        int scroll_delta;
    };
}

#endif
