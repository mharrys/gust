#ifndef PROGRAMIMPL_HPP_INCLUDED
#define PROGRAMIMPL_HPP_INCLUDED

#include "gl.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class RenderStateImpl;
    class ShaderImpl;

    class ProgramImpl {
        friend RenderStateImpl;
    public:
        ProgramImpl();
        ~ProgramImpl();

        int get_uniform_location(std::string const & name);

        void uniform1i(int location, int v0);
        void uniform1f(int location, float v0);
        void uniform2f(int location, float v0, float v1);
        void uniform3f(int location, float v0, float v1, float v2);
        void uniform4f(int location, float v0, float v1, float v2, float v3);
        void uniform1fv(int location, int count, float const * value);
        void uniform_matrix3fv(int location, int count, bool transpose, float const * value);
        void uniform_matrix4fv(int location, int count, bool transpose, float const * value);

        void attach(ShaderImpl & shader);
        void detach(ShaderImpl & shader);

        void bind_attrib_location(int index, std::string const & name);
        bool link();

        std::string get_error_log();
    private:
        void use();

        GLuint id;
    };
}

#endif
