#ifndef PROGRAMPOOL_HPP_INCLUDED
#define PROGRAMPOOL_HPP_INCLUDED

#include "programfactory.hpp"

#include <unordered_map>

namespace gst
{
    typedef std::unordered_map<std::string, Program> ProgramCache;

    // TODO: cache individual shaders, add a file watcher class to track changes in shader files
    class ProgramPool {
    public:
        ProgramPool(ProgramFactory factory);
        Program & create(std::string const & vs_path, std::string const & fs_path);
    private:
        ProgramFactory factory;
        ProgramCache cache;
    };
}

#endif
