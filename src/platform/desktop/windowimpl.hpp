#ifndef WINDOWIMPL_HPP_INCLUDED
#define WINDOWIMPL_HPP_INCLUDED

#include "keyboard.hpp"
#include "mouse.hpp"
#include "resolution.hpp"
#include "translator.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Input;
    class Logger;

    class WindowImpl {
    public:
        WindowImpl(
            std::shared_ptr<Logger> logger,
            bool exit_on_close,
            bool exit_on_esc,
            bool fullscreen,
            bool resize,
            Resolution size,
            std::string title);
        ~WindowImpl();

        bool open();
        bool should_close() const;

        void set_pointer_lock(bool pointer_lock);
        bool get_pointer_lock() const;

        Keyboard get_keyboard() const;
        Mouse get_mouse() const;
        Resolution get_size() const;

        void poll();
        void swap();
    private:
        void on_exit();
        void on_button_down(SDL_Event & event);
        void on_button_up(SDL_Event & event);
        void on_move(SDL_Event & event);
        void on_scroll(SDL_Event & event);
        void on_key_down(SDL_Event & event);
        void on_key_up(SDL_Event & event);
        void on_resize(SDL_Event & event);

        std::shared_ptr<Logger> logger;

        SDL_Window * window;
        SDL_GLContext context;

        bool init;
        bool exit_on_close;
        bool exit_on_esc;
        bool exit_flag;
        bool fullscreen;
        bool pointer_lock;
        bool resize;
        Resolution size;
        std::string title;

        Keyboard keyboard;
        Mouse mouse;

        Translator translator;
    };
}

#endif
