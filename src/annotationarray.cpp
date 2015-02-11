#include "annotationarray.hpp"

gst::AnnotationArray::AnnotationArray(std::string name)
    : index(0),
      begin(name + "["),
      end("].")
{
    // cache default value or format will throw exception if no index is set
    set_current_index(index);
}

std::string gst::AnnotationArray::format(std::string const & annotation) const
{
    return cache.at(index) + annotation;
}

void gst::AnnotationArray::set_current_index(unsigned int index)
{
    this->index = index;
    if (cache.count(index) == 0) {
        cache[index] = begin + std::to_string(index) + end;
    }
}
