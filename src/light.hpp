#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include <memory>
#include <string>

namespace gst
{
    class AnnotationFormatter;
    class UniformCollection;

    // The responsibility of this class is to define a light source from a
    // collection of uniforms.
    class Light {
    public:
        // Construct light from specified uniforms and annotation formatter.
        Light(
            std::shared_ptr<UniformCollection> uniforms,
            std::shared_ptr<AnnotationFormatter> formatter);
        // Return uniforms for this light.
        const std::shared_ptr<UniformCollection> get_uniforms() const;
        // Return annotation formatter for this light.
        const std::shared_ptr<AnnotationFormatter> get_formatter() const;
    private:
        std::shared_ptr<UniformCollection> uniforms;
        std::shared_ptr<AnnotationFormatter> formatter;
    };
}

#endif
