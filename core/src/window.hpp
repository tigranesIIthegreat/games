#pragma once

#include <SDL3/SDL.h>
#include <memory>
#include <string>

namespace core {
class Window {
public:
    Window(const std::string& title, int width, int height);
    ~Window();

public:
    const std::string& title() const;
    int width() const noexcept;
    int height() const noexcept;

public:
    friend class Texture;

private:
    void set_sdl_window();
    void set_sdl_renderer();
    static void _initialize_system();
    static void _deinitialize_system();

public: // to be private
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