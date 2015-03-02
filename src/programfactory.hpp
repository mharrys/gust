#ifndef PROGRAMFACTORY_HPP_INCLUDED
#define PROGRAMFACTORY_HPP_INCLUDED

#include <memory>
#include <vector>

namespace gst
{
    class Logger;
    class GraphicsDevice;
    class Program;
    class Shader;

    class ProgramFactory {
    public:
        ProgramFactory(
            std::shared_ptr<GraphicsDevice> device,
            std::shared_ptr<Logger> logger);
        std::unique_ptr<Program> create_from_file(
            std::string const & vs_path,
            std::string const & fs_path);
        std::unique_ptr<Program> create_from_source(
            std::string const & vs_source,
            std::string const & fs_source);
    private:
        std::shared_ptr<GraphicsDevice> device;
        std::shared_ptr<Logger> logger;
    };
}

#endif
