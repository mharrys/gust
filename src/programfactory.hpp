#ifndef PROGRAMFACTORY_HPP_INCLUDED
#define PROGRAMFACTORY_HPP_INCLUDED

#include "program.hpp"

namespace gst
{
    class Logger;
    class RenderState;
    class Shader;

    class ProgramFactory {
    public:
        ProgramFactory(
            std::shared_ptr<RenderState> render_state,
            std::shared_ptr<Logger> logger);
        Program create_from_file(
            std::string const & vs_path,
            std::string const & fs_path,
            std::vector<AttribLocation> const & locations = {});
        Program create_from_source(
            std::string const & vs_source,
            std::string const & fs_source,
            std::vector<AttribLocation> const & locations = {});
    private:
        std::shared_ptr<RenderState> render_state;
        std::shared_ptr<Logger> logger;
    };
}

#endif
