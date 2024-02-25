#pragma once

#include "rect.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace core {

class Renderable {
public:
    Renderable(Rect coords, Texture& texture, WindowRef window);
    virtual void update_coords() = 0;
    virtual void update_texture();
    virtual void render();

private:
    Rect _coords;
    Texture _texture;
    WindowRef _window;
};

}  // namespace core