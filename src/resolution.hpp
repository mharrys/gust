#ifndef RESOLUTION_HPP_INCLUDED
#define RESOLUTION_HPP_INCLUDED

namespace gst
{
    class Resolution {
    public:
        Resolution();
        Resolution(unsigned int width, unsigned int height);

        bool operator==(Resolution const & other);
        bool operator!=(Resolution const & other);

        unsigned int get_width() const;
        unsigned int get_height() const;
    private:
        unsigned int width;
        unsigned int height;
    };
}

#endif
