#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

namespace gst
{
    class AnnotationFormatter;
    class RenderState;
    class UniformCollection;

    // The responsibility of this class is to mirror a program object on the
    // graphics card.
    class Program {
        friend RenderState;
    public:
        virtual ~Program() = default;
        // Sync specified uniforms with program object on the graphics card,
        // every annotation is formatted with the specified formatter.
        virtual void sync(UniformCollection const & uniforms, AnnotationFormatter const & formatter) = 0;
    protected:
        // Notify graphics card to install program object.
        virtual void use() = 0;
    };
}

#endif
