#ifndef PROGRAM_HPP_INCLUDED
#define PROGRAM_HPP_INCLUDED

namespace gst
{
    class UniformCollection;
    class AnnotationFormatter;

    // The responsibility of this class is to mirror a program object on the
    // graphics card.
    class Program {
    public:
        // Sync specified uniforms with program object on the graphics card,
        // every annotation is formatted with the specified formatter.
        virtual void sync(UniformCollection const & uniforms, AnnotationFormatter const & formatter) = 0;
    protected:
        // Notify graphics card to install program object.
        virtual void use() = 0;
    };
}

#endif
