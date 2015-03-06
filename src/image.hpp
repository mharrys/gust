#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

#include "resolution.hpp"

#include <vector>

namespace gst
{
    // The responsibility of this class is to describe a image.
    class Image {
    public:
        Image() = default;
        Image(Resolution size, std::vector<unsigned char> const & data);
        // Return image size.
        Resolution get_size() const;
        // Return image pixels.
        std::vector<unsigned char> get_data() const;
    private:
        Resolution size;
        std::vector<unsigned char> data;
    };
}

#endif
