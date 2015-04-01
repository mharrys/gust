#include "imagefactory.hpp"

#include "image.hpp"
#include "logger.hpp"
#include "shadoweddataimpl.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

gst::ImageFactory::ImageFactory(std::shared_ptr<Logger> logger)
    : logger(logger)
{
}

gst::Image gst::ImageFactory::create_from_file(std::string const & path)
{
    int width, height, components;
    void * raw_data;

    auto hdr = stbi_is_hdr(path.c_str());
    if (hdr) {
        raw_data = stbi_loadf(path.c_str(), &width, &height, &components, 0);
    } else {
        raw_data = stbi_load(path.c_str(), &width, &height, &components, STBI_rgb_alpha);
    }

    if (!raw_data) {
        logger->log(TRACE("could not create image \"" + path + "\": " + stbi_failure_reason()));
        return Image();
    }

    auto data = std::unique_ptr<ShadowedData>(new ShadowedDataImpl());
    auto size = width * height * components * 1u;

    if (hdr) {
        data->set_float(static_cast<float *>(raw_data), size);
        data->set_float(static_cast<float *>(raw_data), size);
    } else {
        data->set_uchar(static_cast<unsigned char *>(raw_data), size);
    }

    stbi_image_free(raw_data);

    return Image({ width * 1u, height * 1u }, components * 1u, std::move(data));
}
