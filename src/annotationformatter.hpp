#ifndef ANNOTATIONFORMATTER_HPP_INCLUDED
#define ANNOTATIONFORMATTER_HPP_INCLUDED

#include <string>

namespace gst
{
    // The responsibility of this class is to format a annotation for its data
    // structure it currently resides within.
    class AnnotationFormatter {
    public:
        virtual ~AnnotationFormatter() = default;
        // Return formatted annotation.
        virtual std::string format(std::string const & annotation) const = 0;
    };
}

#endif
