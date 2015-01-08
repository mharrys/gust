#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED

#include <memory>

namespace gst
{
    class EventLoop;
    class Input;
    class Resolution;
    class WindowImpl;

    class Window {
        friend EventLoop;
    public:
        Window() = default;
        Window(std::shared_ptr<WindowImpl> impl);

        bool should_close() const;

        void set_pointer_lock(bool pointer_lock);
        bool get_pointer_lock() const;

        Input get_input() const;
        Resolution get_size() const;
    private:
        void poll();
        void swap();

        std::shared_ptr<WindowImpl> impl;
    };
}

#endif
