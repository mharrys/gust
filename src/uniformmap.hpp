#ifndef UNIFORMMAP_HPP_INCLUDED
#define UNIFORMMAP_HPP_INCLUDED

#include "uniformcollection.hpp"

#include <unordered_map>

namespace gst
{
    class UniformMap : public UniformCollection {
    public:
        ShadowedData & get_uniform(std::string const & annotation);
        std::vector<UniformAnnotation> get_uniforms() const;
    private:
        std::unordered_map<std::string, std::shared_ptr<ShadowedData>> uniforms;
    };
}

#endif
