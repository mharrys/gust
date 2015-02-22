#ifndef VIEWPORT_HPP_INCLUDED
#define VIEWPORT_HPP_INCLUDED

namespace gst
{
    class Resolution;

    class Viewport {
    public:
        Viewport();
        Viewport(Resolution resolution);
        Viewport(unsigned int width, unsigned int height);
        Viewport(int x, int y, unsigned int width, unsigned int height);

        bool operator==(Viewport const & other) const;
        bool operator!=(Viewport const & other) const;

        int get_x() const;
        int get_y() const;
        int get_width() const;
        int get_height() const;
    private:
        int x;
        int y;
        unsigned int width;
        unsigned int height;
    };
}

#endif
