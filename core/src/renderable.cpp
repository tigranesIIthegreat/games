#include "renderable.hpp"

namespace core {

Renderable::Renderable(Rect position, TextureRef texture, WindowRef window)
    : _position{position}
    , _texture{texture}
    , _window{window} {}

void Renderable::update() {
    _texture->update();
}

void Renderable::render() {
    _texture->render(_position);
}

void Renderable::set_coords(Point position) {
    _position[0] = position[0];
    _position[1] = position[1];
}

Point Renderable::coords() const {
    return {_position[0], _position[1]};
}

}  // namespace core