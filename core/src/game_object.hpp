#pragma once

#include "input_manager.hpp"
#include "texture.hpp"
#include "window.hpp"

#include <utils/vec.hpp>

namespace core {

class GameObject {
public:
    GameObject() = default;  // TODO: should be removed
    GameObject(Rect position, TextureRef texture);
    virtual ~GameObject() = default;

public:
    virtual void render();
    virtual void set_position(Rect position);
    virtual Rect position() const;
    bool mouse_hovers_over() const;
    virtual void handle_inputs() = 0;

protected:
    Rect _position;
    TextureRef _texture;
    std::vector<std::shared_ptr<GameObject>> _components;
};

}  // namespace core