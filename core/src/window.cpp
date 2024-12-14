#include "window.hpp"

#include <utils/log.hpp>

#include <cassert>

namespace core {

size_t Window::_instance_count = 0;

Window& Window::instance() {
    static auto intance = Window("checkers", 512, 512);
    return intance;
}

Window::Window(const std::string& title, int width, int height)
    : _title(title), _width(width), _height(height), _flags{} {
    if (_instance_count++ == 0)
        _initialize_system();
    set_sdl_window();
    set_sdl_renderer();
    Logger::instance().info("Window created: %s (%d, %d)", title.data(), width, height);
}

Window::~Window() {
    SDL_DestroyRenderer(_sdl_renderer);
    SDL_DestroyWindow(_sdl_window);
    if (--_instance_count == 0) {
        _deinitialize_system();
    }
}

void Window::_initialize_system() {
    if (!SDL_InitSubSystem(0)) {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
}

void Window::_deinitialize_system() {
    SDL_Quit();
}

void Window::set_sdl_window() {
    _sdl_window = SDL_CreateWindow(_title.data(), _width, _height, _flags);
    if (_sdl_window == nullptr) {
        _deinitialize_system();
        throw std::runtime_error(std::string(SDL_GetError()));
    }
}

void Window::set_sdl_renderer() {
    _sdl_renderer = SDL_CreateRenderer(_sdl_window, nullptr);
    if (_sdl_renderer == nullptr) {
        _deinitialize_system();
        throw std::runtime_error(std::string(SDL_GetError()));
    }
}

const std::string& Window::title() const {
    return _title;
}

int Window::width() const noexcept {
    return _width;
}

int Window::height() const noexcept {
    return _height;
}

SDL_Renderer* Window::sdl_renderer() {
    return _sdl_renderer;
}

}  // namespace core