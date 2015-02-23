#ifndef VIEWPORT_HPP_INCLUDED
#define VIEWPORT_HPP_INCLUDED

namespace gst
{
    class Resolution;

    // The responsibility of this class is to describe a viewport shape.
    class Viewport {
    public:
        Viewport();
        Viewport(Resolution resolution);
        Viewport(unsigned int width, unsigned int height);
        Viewport(int x, int y, unsigned int width, unsigned int height);

        // Return true if specified viewport is equal to this viewport, false
        // otherwise.
        bool operator==(Viewport const & other) const;
        // Return true if specified viewport is not equal to this viewport,
        // false otherwise.
        bool operator!=(Viewport const & other) const;

        // Return x-component.
        int get_x() const;
        // Return y-component.
        int get_y() const;
        // Return width-component.
        int get_width() const;
        // Return height-component.
        int get_height() const;
    private:
        int x;
        int y;
        unsigned int width;
        unsigned int height;
    };
}

#endif
