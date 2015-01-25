#ifndef PROGRAMFACTORY_HPP_INCLUDED
#define PROGRAMFACTORY_HPP_INCLUDED

#include "program.hpp"

namespace gst
{
    class Logger;
    class Shader;

    class ProgramFactory {
    public:
        ProgramFactory(
            std::shared_ptr<Logger> logger);
        Program create_from_file(
            std::string const & vs_path,
            std::string const & fs_path,
            std::vector<AttributeLocation> const & locations = {});
        Program create_from_source(
            std::string const & vs_source,
            std::string const & fs_source,
            std::vector<AttributeLocation> const & locations = {});
    private:
        std::shared_ptr<Logger> logger;
    };
}

#endif
