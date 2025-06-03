#include <core/window.hpp>
#include <utils/log.hpp>
#include <emscripten/emscripten.h>
#include <cassert>

EM_JS(int, canvas_get_width, (), { return canvas.width; });
EM_JS(int, canvas_get_height, (), { return canvas.height; });

namespace core {

int Window::_instance_count = 0;

Window& Window::instance() {
    static auto intance = 
        Window("games", canvas_get_width(), canvas_get_height());
    return intance;
}

Window::Window(const std::string& title, int width, int height)
    : _title(title), _width(width), _height(height), _flags{} {

    if (_instance_count++ == 0) {
        _initialize_system();
    }
    set_sdl_window();
    set_sdl_renderer();
    Logger::info(std::format("Window created: {} ({}, {})", title.data(), width, height));
}

Window::~Window() {
    SDL_DestroyRenderer(_sdl_renderer);
    SDL_DestroyWindow(_sdl_window);
    if (--_instance_count == 0) {
        _deinitialize_system();
    }
}

void Window::_initialize_system() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        throw std::runtime_error(std::string(SDL_GetError()));
    }
}

void Window::_deinitialize_system() {
    SDL_Quit();
}

void Window::set_sdl_window() {
    _sdl_window = SDL_CreateWindow(_title.data(), 
                        SDL_WINDOWPOS_CENTERED,
                        SDL_WINDOWPOS_CENTERED, 
                        _width, 
                        _height, 
                        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (_sdl_window == nullptr) {
        _deinitialize_system();
        throw std::runtime_error(std::string(SDL_GetError()));
    }
}

void Window::set_sdl_renderer() {
    _sdl_renderer = SDL_CreateRenderer(_sdl_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (_sdl_renderer == nullptr) {
        _deinitialize_system();
        throw std::runtime_error(std::string(SDL_GetError()));
    }

    // TODO: Set logical size for the renderer if needed
    // this enables flexible window size when resizing the browser window
    // if (!SDL_RenderSetLogicalSize(_sdl_renderer, canvas_get_width(), canvas_get_height())) {
    //     Logger::error(std::format("Failed to set logical size for renderer: {}",
    //         SDL_GetError()));
    // }
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