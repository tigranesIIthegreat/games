#include <core/texture.hpp>

#include <utils/log.hpp>

#include <SDL3_image/SDL_image.h>
#include <fstream>

namespace core {

TextureResource::TextureResource(const std::string& asset_name)
    : _asset_name{asset_name} {
    static auto all_assets = available_assets();
    auto asset = all_assets[_asset_name];
    auto asset_path = "assets/" + std::string(asset["path"]);
    _frame_width = asset["frame_size"]["width"];
    _frame_height = asset["frame_size"]["height"];
    _sdl_texture =
        IMG_LoadTexture(Window::instance().sdl_renderer(), asset_path.data());
    float width{}, height{};
    SDL_GetTextureSize(_sdl_texture, &width, &height);
    _row_count = height / static_cast<int>(_frame_height);
    _col_count = width / static_cast<int>(_frame_width);
    Logger::info(std::format("TextureResource created: {}", asset_name));
}

TextureResource::~TextureResource() {
    SDL_DestroyTexture(_sdl_texture);
}

void TextureResource::render(Rect position, int row, int col) {
    SDL_FRect source{_frame_width * static_cast<float>(col),
                     _frame_height * static_cast<float>(row), _frame_width,
                     _frame_height};
    SDL_FRect sdl_destination{
        static_cast<float>(position[0]), static_cast<float>(position[1]),
        static_cast<float>(position[2]), static_cast<float>(position[3])};

    decltype(auto) renderer = Window::instance().sdl_renderer();
    SDL_RenderTexture(renderer, _sdl_texture, &source, &sdl_destination);
}

nlohmann::json TextureResource::available_assets() {
    static constexpr std::string_view assets_path = "assets/assets.json";
    std::ifstream file(assets_path.data());

    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file assets' file");
    }

    nlohmann::json data;
    file >> data;
    file.close();
    return data["assets"];
}

Texture::Texture(TextureResourceRef resource, int animation_speed)
    : _underlying_resource{resource},
      _animation_speed{animation_speed},
      _current_row{},
      _current_col{} {}

void Texture::update() {
    int ticks = static_cast<int>(SDL_GetTicks() / 50);
    int frameNumber = _animation_speed * ticks;
    int col_count = _underlying_resource->_col_count;
    int row_count = _underlying_resource->_row_count;
    _current_col = frameNumber % col_count;
    _current_row = frameNumber / col_count % row_count;
}

void Texture::render(Rect position) {
    update();
    _underlying_resource->render(position, _current_row, _current_col);
}

TextureFactory& TextureFactory::instance() {
    static TextureFactory instance;
    return instance;
}

TextureRef TextureFactory::create(const std::string& asset_name) {
    auto& resource = _resources[asset_name];
    if (!resource) {
        Logger::info(std::format("Creating texture resource for {}", asset_name));
        resource = TextureResource::make_shared(asset_name);
    } else {
        Logger::info(std::format("Reusing texture resource for {}", asset_name));
    }
    return Texture::make_shared(resource);
}

}  // namespace core