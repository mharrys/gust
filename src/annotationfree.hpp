#ifndef ANNOTATIONFREE_HPP_INCLUDED
#define ANNOTATIONFREE_HPP_INCLUDED

#include "annotationformatter.hpp"

namespace gst
{
    // The responsibility of this class is to format annotations as free
    // variables.
    class AnnotationFree : public AnnotationFormatter {
    public:
        // Return annotation without modification.
        std::string format(std::string const & annotation) const final;
    };
}

#endif
