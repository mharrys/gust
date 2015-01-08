#ifndef STDOUTLOGGER_HPP_INCLUDED
#define STDOUTLOGGER_HPP_INCLUDED

#include "logger.hpp"

namespace gst
{
    class StdoutLogger : public Logger {
    public:
        void log(std::string const & message) override;
    };
}

#endif
