#include "windowimpl.hpp"

#include "logger.hpp"

#include <sstream>

gst::WindowImpl::WindowImpl(
    std::shared_ptr<Logger> logger,
    bool exit_on_close,
    bool exit_on_esc,
    bool fullscreen,
    bool resize,
    Resolution size,
    std::string title)
    : logger(logger),
      window(NULL),
      context(NULL),
      init(false),
      exit_on_close(exit_on_close),
      exit_on_esc(exit_on_esc),
      exit_flag(false),
      fullscreen(fullscreen),
      pointer_lock(false),
      resize(resize),
      size(size),
      title(title)
{
}

gst::WindowImpl::~WindowImpl()
{
    if (context) {
        SDL_GL_DeleteContext(context);
    }
    if (window) {
        SDL_DestroyWindow(window);
    }
    if (init) {
        SDL_Quit();
    }
}

bool gst::WindowImpl::open()
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) {
        logger->log(TRACE("could not initialize SDL: " + std::string(SDL_GetError())));
        return false;
    }
    init = true;

    int mask = SDL_WINDOW_OPENGL;
    mask |= resize     ? SDL_WINDOW_RESIZABLE  : 0;
    mask |= fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    window = SDL_CreateWindow(
        title.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // respect the window manager
        size.get_width(),
        size.get_height(),
        mask
    );
    if (!window) {
        logger->log(TRACE("could not create SDL window:" + std::string(SDL_GetError())));
        return false;
    }

    context = SDL_GL_CreateContext(window);
    if (!context) {
        logger->log(TRACE("coult not create SDL context: " + std::string(SDL_GetError())));
        return false;
    }

    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK) {
        std::stringstream ss;
        ss << glewGetErrorString(glew_error);
        logger->log(TRACE("could not initialize GLEW: " + ss.str()));
        return false;
    }

    if (!GLEW_VERSION_3_0) {
        logger->log(TRACE("requires OpenGL 3.0 API support"));
        return false;
    }

    return true;
}

bool gst::WindowImpl::should_close() const
{
    return exit_flag;
}

gst::Keyboard gst::WindowImpl::get_keyboard() const
{
    return keyboard;
}

gst::Mouse gst::WindowImpl::get_mouse() const
{
    return mouse;
}

void gst::WindowImpl::set_pointer_lock(bool pointer_lock)
{
    if (SDL_SetRelativeMouseMode(pointer_lock ? SDL_TRUE : SDL_FALSE) == 0) {
        this->pointer_lock = pointer_lock;
    }
}

bool gst::WindowImpl::get_pointer_lock() const
{
    return pointer_lock;
}

gst::Resolution gst::WindowImpl::get_size() const
{
    return size;
}

void gst::WindowImpl::poll()
{
    // advance the input device state
    keyboard.tick();
    mouse.tick();

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_QUIT:
            on_exit();
            break;
        case SDL_MOUSEBUTTONDOWN:
            on_button_down(event);
            break;
        case SDL_MOUSEBUTTONUP:
            on_button_up(event);
            break;
        case SDL_MOUSEMOTION:
            on_move(event);
            break;
        case SDL_MOUSEWHEEL:
            on_scroll(event);
            break;
        case SDL_KEYDOWN:
            on_key_down(event);
            break;
        case SDL_KEYUP:
            on_key_up(event);
            break;
        case SDL_WINDOWEVENT:
            if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
                on_resize(event);
            }
            break;
        }
    }
}

void gst::WindowImpl::swap()
{
    SDL_GL_SwapWindow(window);
}

void gst::WindowImpl::on_exit()
{
    if (exit_on_close) {
        exit_flag = true;
    }
}

void gst::WindowImpl::on_button_down(SDL_Event & event)
{
    Button button = translator.translate_button(event.button.button);
    ButtonState state = event.button.clicks > 1 ? ButtonState::DBLCLICKED : ButtonState::CLICKED;
    mouse.buttons[static_cast<int>(button)] = state;
}

void gst::WindowImpl::on_button_up(SDL_Event & event)
{
    Button button = translator.translate_button(event.button.button);
    mouse.buttons[static_cast<int>(button)] = ButtonState::RELEASED;
}

void gst::WindowImpl::on_move(SDL_Event & event)
{
    mouse.position.x = event.motion.x;
    mouse.position.y = event.motion.y;
    mouse.position_rel.x += event.motion.xrel;
    mouse.position_rel.y += event.motion.yrel;
}

void gst::WindowImpl::on_scroll(SDL_Event & event)
{
    mouse.scroll_delta += event.wheel.y;
}

void gst::WindowImpl::on_key_down(SDL_Event & event)
{
    if (event.key.repeat == 0) {
        Key key = translator.translate_key(event.key.keysym.sym);
        keyboard.keys[static_cast<int>(key)] = KeyState::PRESSED;
    }
}

void gst::WindowImpl::on_key_up(SDL_Event & event)
{
    Key key = translator.translate_key(event.key.keysym.sym);
    keyboard.keys[static_cast<int>(key)] = KeyState::RELEASED;

    if (exit_on_esc && key == Key::ESCAPE) {
        exit_flag = true;
    }
}

void gst::WindowImpl::on_resize(SDL_Event & event)
{
    this->size = Resolution(event.window.data1, event.window.data2);
}
