#pragma once

#include <map>
#include <utils/vec.hpp>
#include "window.hpp"

namespace core {

class Texture {
public:
    Texture(const std::string& asset_name);
    void update();
    void render(Rect position);

private:
    std::string _asset_name;
    float _frame_width;
    float _frame_height;
    SDL_Texture* _sdl_texture;
    int _current_row;
    int _current_col;
    int _animation_speed;
    int _row_count;
    int _col_count;
};

using TextureRef = std::shared_ptr<Texture>;

// class TextureManager {
// public:
//     TextureManager();
//     TextureRef create(const std::string& asset_name);

// private:
//     std::map<std::string, TextureRef> _textures;
//     static int _instance_count;
// };

}  // namespace core