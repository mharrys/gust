#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

#include "graphicsresource.hpp"
#include "uniformmap.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Shader;

    typedef std::pair<int, std::string> AttributeLocation;

    // The responsibility of this class is to mirror a program object on the
    // graphics card.
    class Program : public GraphicsResource {
    public:
        virtual ~Program() = default;
        // Merge uniforms with program uniforms. This will override program
        // uniforms at annotation collision.
        virtual void merge_uniforms(UniformMap const & uniforms) = 0;
        // Return attached shaders.
        virtual std::vector<Shader *> get_shaders() = 0;
        // Return attribute locations.
        virtual std::vector<AttributeLocation> get_attribute_locations() const = 0;
        // Return uniforms.
        virtual std::vector<UniformAnnotation> get_uniforms() const = 0;
    };
}

#endif
