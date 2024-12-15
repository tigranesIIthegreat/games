#include "figure.hpp"

namespace checkers {

Figure::Figure(core::Coords coords, int size, Color color, BoardRef board)
    : GameObject{core::Rect{coords[0] * size, coords[1] * size, size, size}}
    , _color{color}
    , _board{board} {
}

Color Figure::color() const {
    return _color;
}

core::Coords Figure::coords() const {
    return {_position[0] / _position[2], _position[1] / _position[3]};
}

void Figure::set_coords(core::Coords coords) {
    _position[0] = coords[0] * _position[2];
    _position[1] = coords[1] * _position[3];
}

}  // namespace checkers