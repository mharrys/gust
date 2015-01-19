#ifndef UNIFORMGROUP_HPP_INCLUDED
#define UNIFORMGROUP_HPP_INCLUDED

#include "uniform.hpp"

#include <string>
#include <unordered_map>

namespace gst
{
    class Program;

    typedef std::unordered_map<std::string, Uniform> UniformLookup;

    class UniformGroup {
        friend Program;
    public:
        UniformGroup();
        UniformGroup(std::string const & name);
        Uniform & operator()(std::string const & uniform_name);
        std::string get_name() const;
        std::string get_name(std::string const & uniform_name) const;
    private:
        std::string name;
        UniformLookup uniforms;
    };
}

#endif
