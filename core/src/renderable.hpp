#pragma once

#include "texture.hpp"
#include "vec.hpp"
#include "window.hpp"

namespace core {

class Renderable {
public:
    Renderable() = default; // TODO: should be removed
    Renderable(Rect position, TextureRef texture);

    virtual ~Renderable() = default;

public:
    void render();

public:
    virtual void set_coords(Point position);
    virtual Point coords() const;

protected:
    Rect _position;
    TextureRef _texture;
    std::vector<std::shared_ptr<Renderable>> _components;
};

}  // namespace core