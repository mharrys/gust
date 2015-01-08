#include "imagefactory.hpp"

#include "image.hpp"
#include "lodepng.hpp"
#include "logger.hpp"

gst::ImageFactory::ImageFactory(std::shared_ptr<Logger> logger)
    : logger(logger)
{
}

gst::Image gst::ImageFactory::create_from_file(std::string const & path)
{
    unsigned int width;
    unsigned int height;
    std::vector<unsigned char> data;

    unsigned int error = lodepng::decode(data, width, height, path.c_str());
    if (error != 0) {
        logger->log(TRACE("could not decode image \"" + path + "\": " + lodepng_error_text(error)));
        return Image();
    }

    return Image({ width, height }, data);
}
