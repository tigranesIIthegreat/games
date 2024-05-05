#pragma once

#include "texture.hpp"
#include "vec.hpp"
#include "window.hpp"

namespace core {

class Renderable {
public:
    Renderable(Rect position, TextureRef texture, WindowRef window);
    virtual ~Renderable() = default;

public:
    virtual void update();
    virtual void render();

public:
    virtual void set_coords(Point position);
    virtual Point coords() const;

protected:
    Rect _position;
    TextureRef _texture;
    WindowRef _window;
};

}  // namespace core