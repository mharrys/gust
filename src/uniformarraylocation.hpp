#ifndef UNIFORMARRAYLOCATION_HPP_INCLUDED
#define UNIFORMARRAYLOCATION_HPP_INCLUDED

#include <unordered_map>
#include <string>

namespace gst
{
    typedef std::unordered_map<unsigned int, std::string> PrefixCache;

    class UniformArrayLocation {
    public:
        UniformArrayLocation(std::string name);
        std::string prefix(unsigned int index);
    private:
        std::string begin;
        std::string end;
        PrefixCache cache;
    };
}

#endif
