#ifndef UNIFORMARRAYELEMENT_HPP_INCLUDED
#define UNIFORMARRAYELEMENT_HPP_INCLUDED

#include "uniformgroup.hpp"

namespace gst
{
    typedef std::unordered_map<unsigned int, std::string> PrefixCache;

    class UniformArrayElement : public UniformGroup {
    public:
        UniformArrayElement(std::string const & name);
        UniformArrayElement & operator=(unsigned int index);
        std::string get_array_name() const;
        std::string get_array_name(std::string const & uniform_name) const;
    private:
        unsigned int index;
        std::string begin;
        std::string end;
        PrefixCache cache;
    };
}

#endif
