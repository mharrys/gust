#ifndef UNIFORMMAP_HPP_INCLUDED
#define UNIFORMMAP_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>

namespace gst
{
    class AnnotationFormatter;
    class ShadowedData;

    typedef std::pair<std::string, std::shared_ptr<ShadowedData>> UniformAnnotation;

    // The responsibility of this class is to associate uniform data with a
    // annotation.
    class UniformMap {
    public:
        virtual ~UniformMap() = default;
        // Return uniform associated with specified annotation, creates a new
        // uniform each time the function is called with a annotation not seen
        // before.
        virtual ShadowedData & get_uniform(std::string const & annotation) = 0;
        // Return all stored uniforms with its associated annotation.
        virtual std::vector<UniformAnnotation> get_uniforms() const = 0;
        // Return associated formatter.
        virtual AnnotationFormatter & get_formatter() const = 0;
    };
}

#endif
