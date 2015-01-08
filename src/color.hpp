#ifndef COLOR_HPP_INCLUDED
#define COLOR_HPP_INCLUDED

#include "glm.hpp"

namespace gst
{
    class Color {
    public:
        Color();
        Color(float red, float green, float blue, float alpha = 1.0f);

        bool operator==(Color const & other);
        bool operator!=(Color const & other);

        float get_red() const;
        float get_green() const;
        float get_blue() const;
        float get_alpha() const;
    private:
        glm::vec4 color;
    };
}

#endif
