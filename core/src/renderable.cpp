#include "renderable.hpp"

namespace core {

Renderable::Renderable(Rect position, TextureRef texture)
    : _position{position}
    , _texture{texture} {}

void Renderable::render() {
    if (_texture) {
        _texture->render(_position);
    }
    for (auto& component : _components) {
        if (component) {
            component->render();
        }
    }
}

void Renderable::set_coords(Point position) {
    _position[0] = position[0];
    _position[1] = position[1];
}

Point Renderable::coords() const {
    return {_position[0], _position[1]};
}

}  // namespace core