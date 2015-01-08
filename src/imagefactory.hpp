#ifndef IMAGEFACTORY_HPP_INCLUDED
#define IMAGEFACTORY_HPP_INCLUDED

#include <memory>
#include <string>

namespace gst
{
    class Image;
    class Logger;

    class ImageFactory {
    public:
        ImageFactory(std::shared_ptr<Logger> logger);
        Image create_from_file(std::string const & path);
    private:
        std::shared_ptr<Logger> logger;
    };
}

#endif
