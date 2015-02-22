#ifndef STDOUTLOGGER_HPP_INCLUDED
#define STDOUTLOGGER_HPP_INCLUDED

#include "logger.hpp"

namespace gst
{
    // The responsibility of this class is to log string messages to standard
    // output.
    class StdoutLogger : public Logger {
    public:
        void log(std::string const & message) override;
    };
}

#endif
