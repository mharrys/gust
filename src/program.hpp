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
        // Attach vertex shader.
        virtual void set_vertex_shader(std::unique_ptr<Shader> vertex_shader) = 0;
        // Attach fragment shader.
        virtual void set_fragment_shader(std::unique_ptr<Shader> fragment_shader) = 0;
        // Set attribute locations. It will bind vertex attribute indices with
        // attribute names.
        virtual void set_attributes(std::vector<AttributeLocation> attribute_locations) = 0;
        // Set uniforms, note that this will only update uniforms from
        // specified collection of uniforms.
        virtual void set_uniforms(UniformMap const & uniforms) = 0;
        // Return attached shaders.
        virtual std::vector<Shader *> get_shaders() = 0;
        // Return attribute locations.
        virtual std::vector<AttributeLocation> get_attribute_locations() const = 0;
        // Return uniforms.
        virtual std::vector<UniformAnnotation> get_uniforms() const = 0;
    };
}

#endif
