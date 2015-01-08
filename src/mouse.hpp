#ifndef MOUSE_HPP_INCLUDED
#define MOUSE_HPP_INCLUDED

#include "button.hpp"
#include "glm.hpp"

#include <vector>

namespace gst
{
    enum class ButtonState {
        UP,
        DOWN,
        CLICKED,
        DBLCLICKED,
        RELEASED
    };

    typedef std::vector<ButtonState> Buttons;

    class Mouse {
    public:
        Mouse();
        void tick();

        Buttons buttons;
        glm::ivec2 position;
        glm::ivec2 position_rel;
        int scroll_delta;
    };
}

#endif
