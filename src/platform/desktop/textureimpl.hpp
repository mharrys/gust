#ifndef TEXTUREIMPL_HPP_INCLUDED
#define TEXTUREIMPL_HPP_INCLUDED

#include "resolution.hpp"
#include "translator.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class FramebufferImpl;
    class RenderStateImpl;
    class TextureParam;

    class TextureImpl {
        friend FramebufferImpl;
        friend RenderStateImpl;
    public:
        TextureImpl(TextureTarget target);
        ~TextureImpl();
        void image2D(Resolution size, std::vector<unsigned char> const & data);
        void parameter(TextureParam const & param);
    private:
        void bind(int unit = 0);
        void translate(TextureParam const & param);

        GLuint id;
        GLenum target;

        GLint internal_format;
        GLint source_format;

        GLint min_filter;
        GLint mag_filter;

        GLint wrap_s;
        GLint wrap_t;

        Translator translator;
    };
}

#endif
