#ifndef SHADERIMPL_HPP_INCLUDED
#define SHADERIMPL_HPP_INCLUDED

#include "graphicsdevice.hpp"
#include "shader.hpp"

#include <memory>
#include <string>

namespace gst
{
    class ShaderImpl : public Shader {
    public:
        ShaderImpl(std::shared_ptr<GraphicsDevice> device, ShaderType type);
        ~ShaderImpl();
        ShaderType get_type() const;
        ShaderHandle get_handle() const;
        // Compile specified source code.
        void compile(std::string const & source);
        // Return true if last compile operation on shader was successful,
        // false otherwise.
        bool get_compile_status() const;
        // Return error message from last compile operation on shader.
        std::string get_compile_error() const;
    private:
        ShaderHandle handle;
        std::shared_ptr<GraphicsDevice> device;

        ShaderType type;

        bool compile_status;
        std::string compile_error;
    };
}

#endif
