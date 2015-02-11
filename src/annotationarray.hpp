#ifndef ANNOTATIONARRAY_HPP_INCLUDED
#define ANNOTATIONARRAY_HPP_INCLUDED

#include "annotationformatter.hpp"

#include <unordered_map>

namespace gst
{
    typedef std::unordered_map<unsigned int, std::string> PrefixCache;

    // The responsibility of this class is to format annotations as array
    // elements.
    class AnnotationArray : public AnnotationFormatter {
    public:
        // Create annotation array with specified name.
        AnnotationArray(std::string name);
        // Return annotation with a named array index prefix.
        std::string format(std::string const & annotation) const;
        // Set the current array element position that will be used in the
        // format.
        void set_current_index(unsigned int index);
    private:
        unsigned int index;
        std::string begin;
        std::string end;
        PrefixCache cache;
    };
}

#endif
