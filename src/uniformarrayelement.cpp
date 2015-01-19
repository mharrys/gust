#include "uniformarrayelement.hpp"

gst::UniformArrayElement::UniformArrayElement(std::string const & name)
    : UniformGroup(name),
      index(0),
      begin(name + "["),
      end("].")
{
}

gst::UniformArrayElement & gst::UniformArrayElement::operator=(unsigned int index)
{
    this->index = index;
    if (cache.count(index) == 0) {
        cache[index] = begin + std::to_string(index) + end;
    }
    return *this;
}

std::string gst::UniformArrayElement::get_array_name() const
{
    return cache.at(index);
}

std::string gst::UniformArrayElement::get_array_name(std::string const & uniform_name) const
{
    return cache.at(index) + uniform_name;
}
