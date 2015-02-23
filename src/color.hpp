#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED

#include "glm.hpp"

namespace gst
{
    // The responsibility of this class is to describe a color in RGBA format.
    class Color {
    public:
        // Construct color with red, green and blue set to 0 and alpha to 1.
        Color();
        // Construct color from specified components.
        Color(float red, float green, float blue, float alpha = 1.0f);

        // Return true if specified color is equal to this color, false
        // otherwise.
        bool operator==(Color const & other);
        // Return true if specified color is not equal to this color, false
        // otherwise.
        bool operator!=(Color const & other);

        // Return red-component.
        float get_red() const;
        // Return green-component.
        float get_green() const;
        // Return blue-component.
        float get_blue() const;
        // Return alpha-component.
        float get_alpha() const;
    private:
        glm::vec4 color;
    };
}

#endif
