#include "window.hpp"

#include "input.hpp"
#include "resolution.hpp"
#include "windowimpl.hpp"

gst::Window::Window(std::shared_ptr<WindowImpl> impl)
    : impl(impl)
{
}

bool gst::Window::should_close() const
{
    return impl.use_count() == 0 || impl->should_close();
}

void gst::Window::set_pointer_lock(bool pointer_lock)
{
    if (get_pointer_lock() != pointer_lock) {
        impl->set_pointer_lock(pointer_lock);
    }
}

bool gst::Window::get_pointer_lock() const
{
    return impl->get_pointer_lock();
}

gst::Input gst::Window::get_input() const
{
    return Input(impl->get_keyboard(), impl->get_mouse());
}

gst::Resolution gst::Window::get_size() const
{
    return impl->get_size();
}

void gst::Window::poll()
{
    impl->poll();
}

void gst::Window::swap()
{
    impl->swap();
}
