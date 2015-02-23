#ifndef BUTTON_HPP_INCLUDED
#define BUTTON_HPP_INCLUDED

namespace gst
{
    // Supported mouse buttons.
    enum class Button {
        UNKNOWN, // Unknown button.
        LEFT,    // Left button or Mouse 1.
        MIDDLE,  // Middle button or Mouse 3.
        RIGHT,   // Right button or Mouse 2.
        X1,      // Extra button 1 or Mouse 4.
        X2,      // Extra button 2 or Mouse 5.
        COUNT
    };
}

#endif
