#include "uniformarraylocation.hpp"

gst::UniformArrayLocation::UniformArrayLocation(std::string name)
    : begin(name + "["),
      end("].")
{
}

std::string gst::UniformArrayLocation::prefix(unsigned int index)
{
    if (cache.count(index) == 0) {
        cache[index] = begin + std::to_string(index) + end;
    }
    return cache.at(index);
}
