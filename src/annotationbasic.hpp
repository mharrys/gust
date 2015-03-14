#ifndef ANNOTATIONBASIC_HPP_INCLUDED
#define ANNOTATIONBASIC_HPP_INCLUDED

#include "annotationformatter.hpp"

namespace gst
{
    // The responsibility of this class is to format annotations as free
    // variables.
    class AnnotationBasic : public AnnotationFormatter {
    public:
        // Return annotation without modification.
        std::string format(std::string const & annotation) const final;
    };
}

#endif
