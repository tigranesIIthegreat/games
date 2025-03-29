#pragma once

#include <map>
#include <utils/vec.hpp>
#include <nlohmann/json.hpp>

#include "window.hpp"

namespace core {

struct TextureResource {
public:
    ~TextureResource();

private:
    TextureResource(const std::string& asset_name);
    void render(Rect position, int row, int col);
    static nlohmann::json available_assets();

private:
    std::string _asset_name;
    float _frame_width;
    float _frame_height;
    SDL_Texture* _sdl_texture;
    int _row_count;
    int _col_count;

private:
    template<typename... Args>
    static std::shared_ptr<TextureResource> make_shared(Args... args) {
        auto* raw_ptr = new TextureResource(args...);
        return std::shared_ptr<TextureResource>(raw_ptr);
    }

public:
    friend class Texture;
    friend class TextureFactory;
};

using TextureResourceRef = std::shared_ptr<TextureResource>;

class Texture {
public:
    void render(Rect position);

private:
    Texture(TextureResourceRef resource, int animation_speed = 1);
    void update();

private:
    TextureResourceRef _underlying_resource;
    int _animation_speed;
    int _current_row;
    int _current_col;

private:
    template <typename... Args>
    static std::shared_ptr<Texture> make_shared(Args... args) {
        auto* raw_ptr = new Texture(args...);
        return std::shared_ptr<Texture>(raw_ptr);
    }

public:
    friend class TextureFactory;
};

using TextureRef = std::shared_ptr<Texture>;

class TextureFactory {
public:
    static TextureFactory& instance();
    TextureRef create(const std::string& asset_name);

private:
    TextureFactory() = default;

private:
    std::unordered_map<std::string, TextureResourceRef> _resources;
};

}  // namespace core