#include "texture.hpp"

#include <SDL3_image/SDL_image.h>

namespace core {

Texture::Texture(const std::string& path, float frame_width, float frame_heigth,
                 WindowRef window)
    : _path{path},
      _frame_width{frame_width},
      _frame_height{frame_heigth},
      _window{window},
      _current_row{},
      _current_col{},
      _animation_speed{1} {

    _sdl_texture = IMG_LoadTexture(_window->_sdl_renderer, path.data()); 
    int width{}, height{};
    SDL_QueryTexture(_sdl_texture, nullptr, nullptr, &width, &height);
    
    _row_count = height / static_cast<int>(_frame_height);
    _col_count = width / static_cast<int>(_frame_width);
}

void Texture::update() {
    size_t ticks = static_cast<size_t>(SDL_GetTicks() / 50);
    size_t frameNumber = _animation_speed * ticks;
    _current_col = frameNumber % _col_count;
    _current_row = frameNumber / _col_count % _row_count;
}

void Texture::render(Vec2 coords, float width, float height) {
    SDL_FRect source{_frame_width * static_cast<float>(_current_col),
                     _frame_height * static_cast<float>(_current_row),
                     _frame_width, _frame_height};
    SDL_FRect destination{coords[0], coords[1], width, height};

    SDL_RenderTexture(_window->_sdl_renderer, _sdl_texture, &source, &destination);
}

}  // namespace core