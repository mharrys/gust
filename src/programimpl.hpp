#ifndef PROGRAMIMPL_HPP_INCLUDED
#define PROGRAMIMPL_HPP_INCLUDED

#include "graphicsdevice.hpp"
#include "program.hpp"

#include <memory>
#include <unordered_map>

namespace gst
{
    class Logger;
    class Shader;

    typedef std::unordered_map<std::string, int> LocationCache;

    class ProgramImpl : public Program {
    public:
        ProgramImpl(std::shared_ptr<GraphicsDevice> device, std::shared_ptr<Logger> logger);
        ~ProgramImpl();
        void sync(UniformCollection const & uniforms, AnnotationFormatter const & formatter);
        // Attach shader to this program.
        void attach(Shader const & shader);
        // Detach shader from this program. The shader will remain attached if
        // detached after link operation.
        void detach(Shader const & shader);
        // Bind attribute location with specified vertex attribute index and
        // specified attribute name.
        void bind_attribute(int index, std::string const & name);
        // Links program.
        void link();
        // Return true if last link operation was successful, false otherwise.
        bool get_link_status() const;
        // Return error message from last link operation.
        std::string get_link_error() const;
    private:
        void use();
        int get_cached_location(std::string const & annotation);

        ProgramHandle handle;
        std::shared_ptr<GraphicsDevice> device;

        LocationCache locations;
        std::shared_ptr<Logger> logger;

        bool link_status;
        std::string link_error;
    };
}

#endif
