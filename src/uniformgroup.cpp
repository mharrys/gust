#include "uniformgroup.hpp"

gst::UniformGroup::UniformGroup()
    : name("")
{
}

gst::UniformGroup::UniformGroup(std::string const & name)
    : name(name)
{
}

gst::Uniform & gst::UniformGroup::operator()(std::string const & uniform_name)
{
    if (uniforms.count(uniform_name) == 0) {
        uniforms[uniform_name] = Uniform();
    }
    return uniforms.at(uniform_name);
}

std::string gst::UniformGroup::get_name() const
{
    return name;
}

std::string gst::UniformGroup::get_name(std::string const & uniform_name) const
{
    if (name.empty()) {
        return uniform_name;
    } else {
        return name + "." + uniform_name;
    }
}
