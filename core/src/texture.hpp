#pragma once

#include "rect.hpp"
#include "window.hpp"

#include <string>

#include <SDL3/SDL.h>

namespace core {

class Texture {
public:
    Texture(const std::string& path, float frame_width, float frame_heigth,
            WindowRef window);

public:
    void update();
    void render(Rect destination);

private:
    std::string _path;
    float _frame_width;
    float _frame_height;
    WindowRef _window;
    SDL_Texture* _sdl_texture;
    size_t _current_row;
    size_t _current_col;
    size_t _animation_speed;
    size_t _row_count;
    size_t _col_count;
};

}  // namespace core