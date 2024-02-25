#include "movable.hpp"

namespace core {

Movable::Movable(Vec2 coords, float width, float height, Texture& texture,
                 WindowRef window, Vec2 velocity, Vec2 acceleration)
                : Renderable(coords, width, height, texture, window)
                , _velocity{velocity}
                , _acceleration{acceleration} {}

void Movable::update_coords() {
    _velocity += _acceleration;
    _coords += _velocity;
}

} // namespace core