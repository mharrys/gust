#include "windowbuilder.hpp"

#include "windowimpl.hpp"

gst::WindowBuilder::WindowBuilder(std::shared_ptr<Logger> logger)
    : logger(logger),
      exit_on_close(true),
      exit_on_esc(true),
      fullscreen(false),
      resize(false),
      size(800, 600),
      title("Unnamed Window")
{
}

void gst::WindowBuilder::set_exit_on_close(bool exit_on_close)
{
    this->exit_on_close = exit_on_close;
}

void gst::WindowBuilder::set_exit_on_esc(bool exit_on_esc)
{
    this->exit_on_esc = exit_on_esc;
}

void gst::WindowBuilder::set_fullscreen(bool fullscreen)
{
    this->fullscreen = fullscreen;
}

void gst::WindowBuilder::set_resize(bool resize)
{
    this->resize = resize;
}

void gst::WindowBuilder::set_size(Resolution size)
{
    this->size = size;
}

void gst::WindowBuilder::set_title(std::string title)
{
    this->title = title;
}

std::unique_ptr<gst::Window> gst::WindowBuilder::build()
{
    auto window = std::unique_ptr<WindowImpl>(new WindowImpl(
        logger,
        exit_on_close,
        exit_on_esc,
        fullscreen,
        resize,
        size,
        title
    ));
    window->open();
    return std::move(window);
}
