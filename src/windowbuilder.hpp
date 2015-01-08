#ifndef WINDOWBUILDER_HPP_INCLUDED
#define WINDOWBUILDER_HPP_INCLUDED

#include "resolution.hpp"

#include <memory>
#include <string>

namespace gst
{
    class Logger;
    class Window;

    class WindowBuilder {
    public:
        WindowBuilder(std::shared_ptr<Logger> logger);
        void set_exit_on_close(bool exit_on_close);
        void set_exit_on_esc(bool exit_on_esc);
        void set_fullscreen(bool fullscreen);
        void set_resize(bool resize);
        void set_size(Resolution size);
        void set_title(std::string title);
        Window build();
    private:
        std::shared_ptr<Logger> logger;
        bool exit_on_close;
        bool exit_on_esc;
        bool fullscreen;
        bool resize;
        Resolution size;
        std::string title;
    };
}

#endif
