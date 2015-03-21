#ifndef PROGRAMFACTORY_HPP_INCLUDED
#define PROGRAMFACTORY_HPP_INCLUDED

#include <memory>
#include <vector>

namespace gst
{
    class Logger;
    class Program;
    class Shader;

    // The responsibility of this class is to build a program.
    class ProgramFactory {
    public:
        ProgramFactory(std::shared_ptr<Logger> logger);
        // Return created program with shaders read from file.
        std::unique_ptr<Program> create_from_file(
            std::string const & vs_path,
            std::string const & fs_path);
        // Return created program with shaders read from source.
        std::unique_ptr<Program> create_from_source(
            std::string const & vs_source,
            std::string const & fs_source);
    private:
        std::shared_ptr<Logger> logger;
    };
}

#endif
