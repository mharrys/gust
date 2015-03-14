#ifndef ANNOTATIONSTRUCT_HPP_INCLUDED
#define ANNOTATIONSTRUCT_HPP_INCLUDED

#include "annotationformatter.hpp"

namespace gst
{
    // The responsibility of this class is to format annotations as structs.
    class AnnotationStruct : public AnnotationFormatter {
    public:
        // Create annotation struct with specified name.
        AnnotationStruct(std::string name);
        // Return annoation with a named struct prefix.
        std::string format(std::string const & annotation) const final;
    private:
        std::string name;
    };
}

#endif
