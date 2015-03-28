#ifndef PROGRAMPOOL_HPP_INCLUDED
#define PROGRAMPOOL_HPP_INCLUDED

#include <memory>
#include <string>
#include <unordered_map>

namespace gst
{
    class Logger;
    class Program;

    typedef std::unordered_map<std::string, std::shared_ptr<Program>> ProgramCache;

    // The responsibility of this class is to cache every program so that no
    // program is ever read in twice but instead is reused.
    class ProgramPool {
    public:
        ProgramPool(std::shared_ptr<Logger> logger);
        // Return created/cached program with shaders read from file.
        std::shared_ptr<Program> create(
            std::string const & vs_path,
            std::string const & fs_path);
    private:
        std::shared_ptr<Logger> logger;
        ProgramCache cache;
    };
}

#endif
