#pragma once

#include "texture.hpp"
#include "vec.hpp"
#include "window.hpp"

namespace core {

class Renderable {
public:
    Renderable() = default;
    Renderable(Rect position, TextureRef texture);
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
};

}  // namespace core