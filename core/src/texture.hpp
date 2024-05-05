#pragma once

#include "vec.hpp"
#include "window.hpp"

#include <SDL3/SDL.h>

#include <memory>
#include <string>

namespace core {

class Texture {
public:
    Texture(const std::string& asset_name, WindowRef window);

public:
    void update();
    void render(Rect position);

private:
    std::string _asset_name;
    WindowRef _window;
    float _frame_width;
    float _frame_height;
    SDL_Texture* _sdl_texture;
    size_t _current_row;
    size_t _current_col;
    size_t _animation_speed;
    size_t _row_count;
    size_t _col_count;
};

using TextureRef = std::shared_ptr<Texture>;

}  // namespace core