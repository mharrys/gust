#ifndef UNIFORMMAPIMPL_HPP_INCLUDED
#define UNIFORMMAPIMPL_HPP_INCLUDED

#include "uniformmap.hpp"

#include <unordered_map>

namespace gst
{
    class UniformMapImpl : public UniformMap {
    public:
        UniformMapImpl(std::shared_ptr<AnnotationFormatter> formatter);
        ShadowedData & get_uniform(std::string const & annotation) final;
        std::vector<UniformAnnotation> get_uniforms() const final;
        AnnotationFormatter & get_formatter() const final;
    private:
        std::unordered_map<std::string, std::shared_ptr<ShadowedData>> uniforms;
        std::shared_ptr<AnnotationFormatter> formatter;
    };
}

#endif
