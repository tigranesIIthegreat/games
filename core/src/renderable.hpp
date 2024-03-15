#pragma once

#include "vec.hpp"
#include "texture.hpp"
#include "window.hpp"

namespace core {

class Renderable {
public:
    Renderable(Vec2 coords, float width, float height, TextureRef texture, WindowRef window);
    virtual ~Renderable() = default;

public:
    virtual void update();
    virtual void render();

protected:
    Vec2 _coords;
    float _width;
    float _height;
    TextureRef _texture;
    WindowRef _window;
};

}  // namespace core