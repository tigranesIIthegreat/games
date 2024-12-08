#pragma once

#include "input_manager.hpp"
#include "texture.hpp"
#include "vec.hpp"
#include "window.hpp"

namespace core {

class GameObject {
public:
    GameObject() = default;  // TODO: should be removed
    GameObject(Rect position, TextureRef texture);
    virtual ~GameObject() = default;

public:
    virtual void render();
    virtual void set_coords(Point position);
    virtual Point coords() const;
    bool mouse_hovers_over() const;
    virtual void handle_inputs() = 0;

protected:
    Rect _position;
    TextureRef _texture;
    std::vector<std::shared_ptr<GameObject>> _components;
};

}  // namespace core