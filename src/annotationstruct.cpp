#include "annotationstruct.hpp"

gst::AnnotationStruct::AnnotationStruct(std::string name)
    : name(name)
{
}

std::string gst::AnnotationStruct::format(std::string const & annotation) const
{
    return name + "." + annotation;
}
