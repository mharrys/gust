#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include <memory>
#include <string>

namespace gst
{
    class UniformCollection;

    // The responsibility of this class is to define a light source from a
    // collection of uniforms.
    class Light {
    public:
        Light(std::shared_ptr<UniformCollection> uniforms);
        // Return uniforms for this light.
        std::shared_ptr<UniformCollection> get_uniforms() const;
    private:
        std::shared_ptr<UniformCollection> uniforms;
    };
}

#endif
