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
    SDL_Surface* surface = IMG_Load(path.data());
    _sdl_texture =
        SDL_CreateTextureFromSurface(_window->_sdl_renderer, surface);
    SDL_DestroySurface(surface);
    int width{};
    int height{};
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

void Texture::render(Rect destination) {
    SDL_FRect src{_frame_width * static_cast<float>(_current_col),
                  _frame_height * static_cast<float>(_current_row),
                  _frame_width, _frame_height};
    SDL_FRect dst{destination.x, destination.y, destination.width, destination.height};
    SDL_RenderTexture(_window->_sdl_renderer, _sdl_texture, &src, &dst);
}

}  // namespace core