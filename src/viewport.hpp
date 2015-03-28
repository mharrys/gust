#ifndef VIEWPORT_HPP_INCLUDED
#define VIEWPORT_HPP_INCLUDED

namespace gst
{
    class Resolution;

    // The responsibility of this class is to describe a viewport.
    class Viewport {
    public:
        // Construct viewport with 0 x, y, width and height.
        Viewport();
        // Construct viewport with specified widh and height of a resolution
        // and with 0 x and y.
        Viewport(Resolution resolution);
        // Construct viewport with specified width and height and with 0 x and y.
        Viewport(unsigned int width, unsigned int height);
        // Construct viewport with specified x, y, width and height.
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
        unsigned int get_width() const;
        // Return height-component.
        unsigned int get_height() const;
    private:
        int x;
        int y;
        unsigned int width;
        unsigned int height;
    };
}

#endif
