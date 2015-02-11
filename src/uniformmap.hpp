#ifndef UNIFORMMAP_HPP_INCLUDED
#define UNIFORMMAP_HPP_INCLUDED

#include "uniformcollection.hpp"

#include <unordered_map>

namespace gst
{
    class UniformMap : public UniformCollection {
    public:
        Uniform & get_uniform(std::string const & annotation);
        std::vector<UniformAnnotation> get_uniforms() const;
    private:
        std::unordered_map<std::string, Uniform> uniforms;
    };
}

#endif
