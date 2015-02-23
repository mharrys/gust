#ifndef RESOLUTION_HPP_INCLUDED
#define RESOLUTION_HPP_INCLUDED

namespace gst
{
    // The responsibility of this class is to describe a resolution.
    class Resolution {
    public:
        // Construct resolution with 0 width and height.
        Resolution();
        // Construct resolution with equal width and height.
        Resolution(unsigned int size);
        // Construct resolution with specified with and height.
        Resolution(unsigned int width, unsigned int height);

        // Return true if specified resolution is equal to this resolution,
        // false otherwise.
        bool operator==(Resolution const & other);
        // Return true if specified resolution is not equal to this viewport,
        // false otherwise.
        bool operator!=(Resolution const & other);

        // Return width.
        unsigned int get_width() const;
        // Return height.
        unsigned int get_height() const;
    private:
        unsigned int width;
        unsigned int height;
    };
}

#endif
