#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>

namespace core {
class Window {
public:
    static Window& instance();
    ~Window();

public:
    const std::string& title() const;
    int width() const noexcept;
    int height() const noexcept;
    SDL_Renderer* sdl_renderer();

private:
    Window(const std::string& title, int width, int height);

private:
    void set_sdl_window();
    void set_sdl_renderer();
    static void _initialize_system();
    static void _deinitialize_system();

private:
    std::string _title;
    int _width{};
    int _height{};
    int _flags{};
    SDL_Window* _sdl_window{};
    SDL_Renderer* _sdl_renderer{};

private:
    static size_t _instance_count;
};

using WindowRef = std::shared_ptr<Window>;

}  // namespace core