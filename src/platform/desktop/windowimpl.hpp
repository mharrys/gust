#ifndef WINDOWIMPL_HPP_INCLUDED
#define WINDOWIMPL_HPP_INCLUDED

#include "keyboard.hpp"
#include "mouse.hpp"
#include "resolution.hpp"
#include "window.hpp"

#include "gl.hpp"
#include "sdl.hpp"

#include <memory>
#include <vector>

namespace gst
{
    class Logger;

    class WindowImpl : public Window {
    public:
        // Construct window with specified settings. It will remain closed
        // until a successful call to open.
        WindowImpl(
            std::shared_ptr<Logger> logger,
            bool exit_on_close,
            bool exit_on_esc,
            bool fullscreen,
            bool resize,
            Resolution size,
            std::string title);
        ~WindowImpl();

        // Return true if window was opened successfully, false otherwise.
        bool open();
        bool should_close() const final;

        void poll() final;
        void swap() final;

        void set_pointer_lock(bool pointer_lock) final;
        bool get_pointer_lock() const final;

        Input get_input() const final;
        Resolution get_size() const final;
    private:
        void advance_input();

        void on_exit();
        void on_button_down(SDL_Event & event);
        void on_button_up(SDL_Event & event);
        void on_move(SDL_Event & event);
        void on_scroll(SDL_Event & event);
        void on_key_down(SDL_Event & event);
        void on_key_up(SDL_Event & event);
        void on_resize(SDL_Event & event);

        Button translate_button(int button) const;
        Key translate_key(int key) const;

        std::shared_ptr<Logger> logger;

        bool init_sdl;
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

        SDL_Window * window;
        SDL_GLContext context;
    };
}

#endif
