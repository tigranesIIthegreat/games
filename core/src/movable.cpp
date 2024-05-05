#include "movable.hpp"

namespace core {

Movable::Movable(Rect position, TextureRef texture, WindowRef window,
                 Point velocity, Point acceleration)
    : Renderable(position, texture, window),
      _velocity{velocity},
      _acceleration{acceleration} {}

void Movable::update() {
    Renderable::update();
    _velocity += _acceleration;
    _position[0] += _velocity[0];
    _position[1] += _velocity[1];
}

}  // namespace core