#include "stdoutlogger.hpp"

#include <iostream>

void gst::StdoutLogger::log(std::string const & message)
{
    std::cout << message << std::endl;
}
