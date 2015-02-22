#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

namespace gst
{
    class Input;
    class Resolution;

    // The responsibility of this class is to interact with a system window.
    class Window {
    public:
        // Return true if system window has not been opened or if there has
        // been a request to close the system window, false otherwise.
        virtual bool should_close() const = 0;
        // Poll events from the system window.
        virtual void poll() = 0;
        // Swap frontbuffer and backbuffer.
        virtual void swap() = 0;
        // Set pointer lock enabled/disabled, if enabled the pointer should be
        // locked at the center of the window.
        virtual void set_pointer_lock(bool pointer_lock) = 0;
        // Return pointer lock state.
        virtual bool get_pointer_lock() const = 0;
        // Return input state.
        virtual Input get_input() const = 0;
        // Return window client bounds (decorations excluded).
        virtual Resolution get_size() const = 0;
    };
}

#endif
