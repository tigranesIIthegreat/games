#include "texture.hpp"

#include <nlohmann/json.hpp>
#include <SDL3_image/SDL_image.h>

#include <fstream>

namespace core {

namespace {

nlohmann::json assets() {
    static constexpr std::string_view assets_path = "assets/assets.json";
    std::ifstream file(assets_path);

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file assets' file");
    }

    nlohmann::json data;
    file >> data;
    file.close();
    return data["assets"];
}

} // namespace

Texture::Texture(const std::string& asset_name, WindowRef window)
    : _asset_name{asset_name}
    , _window{window}
    , _current_row{}
    , _current_col{}
    , _animation_speed{1} {

    static auto all_assets = assets();
    auto asset = all_assets[asset_name];

    auto asset_path = "assets/" + std::string(asset["path"]);
    _frame_width = asset["frame_size"]["width"];
    _frame_height = asset["frame_size"]["height"];

    _sdl_texture = IMG_LoadTexture(_window->_sdl_renderer, asset_path.data()); 
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

    // TODO: SDL_SetTextureColorMod(_sdl_texture, 200, 200, 200);
    SDL_RenderTexture(_window->_sdl_renderer, _sdl_texture, &source, &destination);
}

}  // namespace core