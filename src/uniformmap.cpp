#include "uniformmap.hpp"

gst::Uniform & gst::UniformMap::get_uniform(std::string const & annotation)
{
    if (uniforms.count(annotation) == 0) {
        uniforms[annotation] = Uniform();
    }
    return uniforms.at(annotation);
}

std::vector<gst::UniformAnnotation> gst::UniformMap::get_uniforms() const
{
    std::vector<UniformAnnotation> result;
    for (auto & uniform : uniforms) {
        result.push_back(uniform);
    }
    return result;
}
