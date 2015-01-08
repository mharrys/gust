#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

#include "resolution.hpp"

#include <vector>

namespace gst
{
    class Image {
    public:
        Image() = default;
        Image(Resolution size, std::vector<unsigned char> const & data);
        Resolution get_size() const;
        std::vector<unsigned char> get_data() const;
    private:
        Resolution size;
        std::vector<unsigned char> data;
    };
}

#endif
