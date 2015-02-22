#ifndef LOGGER_HPP_INCLUDED
#define LOGGER_HPP_INCLUDED

#include <string>

// https://stackoverflow.com/questions/2670816/how-can-i-use-the-compile-time-constant-line-in-a-string
#define STRINGIZE_DETAIL(x) #x
#define STRINGIZE(x) STRINGIZE_DETAIL(x)
#define TRACE(msg) (__FILE__ " line " STRINGIZE(__LINE__) ": " msg)

namespace gst
{
    // The responsibility of this class is to log string messages.
    class Logger {
    public:
        virtual ~Logger() = default;
        // Log specified message.
        virtual void log(std::string const & message) = 0;
    };
}

#endif
