#include "game_object.hpp"

namespace core {

GameObject::GameObject(Rect position, TextureRef texture)
    : _position{position}, _texture{texture} {}

void GameObject::render() {
    if (_texture) {
        _texture->render(_position);
    }
    for (auto& component : _components) {
        if (component) {
            component->render();
        }
    }
}

void GameObject::set_coords(Point position) {
    _position[0] = position[0];
    _position[1] = position[1];
}

Point GameObject::coords() const {
    return {_position[0], _position[1]};
}

bool GameObject::mouse_hovers_over() const {
    auto mouse_position =
        core::input::InputManager::get_instance().mouse_position();
    return _position[0] <= mouse_position[0] and
           mouse_position[0] <= _position[0] + _position[2] and
           _position[1] <= mouse_position[1] and
           mouse_position[1] <= _position[1] + _position[3];
}

}  // namespace core