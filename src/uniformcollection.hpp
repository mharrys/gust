#ifndef UNIFORMCOLLECTION_HPP_INCLUDED
#define UNIFORMCOLLECTION_HPP_INCLUDED

#include "uniform.hpp"

#include <string>

namespace gst
{
    typedef std::pair<std::string, Uniform> UniformAnnotation;

    // The responsibility of this class is to associate uniform data with a
    // annotation.
    class UniformCollection {
    public:
        // Return uniform associated with specified annotation, creates a new
        // uniform each time the function is called with a annotation not seen
        // before.
        virtual Uniform & get_uniform(std::string const & annotation) = 0;
        // Return all stored uniforms with its associated annotation.
        virtual std::vector<UniformAnnotation> get_uniforms() const = 0;
    };
}

#endif
