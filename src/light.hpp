#ifndef LIGHT_HPP_INCLUDED
#define LIGHT_HPP_INCLUDED

#include <memory>
#include <string>

namespace gst
{
    class ShadowedData;
    class UniformMap;

    // The responsibility of this class is to define a light source from a
    // collection of uniforms.
    class Light {
    public:
        static Light create_basic();
        static Light create_struct(std::string const & name);
        static Light create_array(std::string const & name);

        Light() = default;
        Light(std::shared_ptr<UniformMap> uniforms);

        // Return uniform associated with specified annotation.
        ShadowedData & operator[](std::string const & annotation);

        // Set light enabled/disabled.
        void set_enabled(bool enabled);
        // Return true if enabled, false otherwise.
        bool get_enabled() const;
        // Return all uniforms that defines this light source.
        UniformMap & get_uniforms();
    private:
        std::shared_ptr<UniformMap> uniforms;
        bool enabled;
    };
}

#endif
