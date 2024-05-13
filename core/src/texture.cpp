#include "texture.hpp"

#include <SDL3_image/SDL_image.h>
#include <nlohmann/json.hpp>

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

}  // namespace

Texture::Texture(const std::string& asset_name)
    : _asset_name{asset_name},
      _current_row{},
      _current_col{},
      _animation_speed{1}{

    static auto all_assets = assets();
    auto asset = all_assets[asset_name];

    auto asset_path = "assets/" + std::string(asset["path"]);
    _frame_width = asset["frame_size"]["width"];
    _frame_height = asset["frame_size"]["height"];

    _sdl_texture = IMG_LoadTexture(Window::get_instance()._sdl_renderer, asset_path.data());
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

void Texture::render(Rect position) {
    SDL_FRect source{_frame_width * static_cast<float>(_current_col),
                     _frame_height * static_cast<float>(_current_row),
                     _frame_width, _frame_height};
    SDL_FRect sdl_destination{position[0], position[1], position[2],
                              position[3]};

    SDL_RenderTexture(Window::get_instance()._sdl_renderer, _sdl_texture, &source,
                      &sdl_destination);
}

size_t TextureManager::_instance_count = 0;

TextureManager::TextureManager() 
    : _textures{} {
    if (_instance_count++ != 0)
        throw std::runtime_error("only one instance of Texture Manager can be instanciated");
}

TextureRef TextureManager::create(const std::string& asset_name) {
    if (_textures.find(asset_name) == _textures.end()) {
        auto texture = std::make_shared<Texture>(asset_name);
        // _textures.emplace(std::make_pair(asset_name, texture));
    }
    return _textures[asset_name];
}

}  // namespace core