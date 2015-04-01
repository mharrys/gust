#ifndef IMAGE_HPP_INCLUDED
#define IMAGE_HPP_INCLUDED

#include "resolution.hpp"

#include <memory>

namespace gst
{
    class ShadowedData;

    // The responsibility of this class is to describe a image.
    class Image {
    public:
        // Construct empty image.
        Image() = default;
        // Construct image with specified size, number of components and data.
        Image(
            Resolution size,
            unsigned int components,
            std::unique_ptr<ShadowedData> data);
        // Return width and height.
        Resolution get_size() const;
        // Return width.
        unsigned int get_width() const;
        // Return height.
        unsigned int get_height() const;
        // Return number of components.
        unsigned int get_components() const;
        // Return data.
        ShadowedData const & get_data() const;
        // Return raw data as unsigned char.
        unsigned char const * get_uchar_pixels() const;
        // Return raw data as float.
        float const * get_float_pixels() const;
    private:
        Resolution size;
        unsigned int components;
        std::unique_ptr<ShadowedData> data;
    };
}

#endif
