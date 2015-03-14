#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include <memory>
#include <string>

namespace gst
{
    class UniformMap;

    // The responsibility of this class is to define a light source from a
    // collection of uniforms.
    class Light {
    public:
        Light(std::shared_ptr<UniformMap> uniforms);
        // Set light enabled/disabled.
        void set_enabled(bool enabled);
        // Return uniforms for this light.
        std::shared_ptr<UniformMap> get_uniforms() const;
        // Return true if enabled, false otherwise.
        bool get_enabled() const;
    private:
        std::shared_ptr<UniformMap> uniforms;
        bool enabled;
    };
}

#endif
