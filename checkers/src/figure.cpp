#include "figure.hpp"

namespace checkers {

core::TextureRef Figure::_white_man_texture =
    std::make_shared<core::Texture>("man_white");

core::TextureRef Figure::_black_man_texture =
    std::make_shared<core::Texture>("man_black");

core::TextureRef Figure::_white_king_texture =
    std::make_shared<core::Texture>("king_white");

core::TextureRef Figure::_black_king_texture =
    std::make_shared<core::Texture>("king_black");

Figure::Figure(core::Coords coords, int size, Color color)
    : GameObject{core::Rect{coords[0] * size, coords[1] * size, size, size}, nullptr}
    , _color{color}
    , _is_king{false}
    , _is_selected{false} {
    if (color == Color::WHITE) {
        _texture = _white_man_texture;
    } else {
        _texture = _black_man_texture;
    }
}

Color Figure::color() const {
    return _color;
}

bool Figure::is_king() const {
    return _is_king;
}
bool Figure::is_selected() const {
    return _is_selected;
}

void Figure::handle_inputs() {
    if (mouse_hovers_over()) {
        // TODO: mouse hovers
    } else {
        // TODO: mouse does not hover
    }
}

core::Coords Figure::coords() const {
    return {_position[0] / _position[2], _position[1] / _position[3]};
}

void Figure::set_coords(core::Coords coords) {
    _position[0] = coords[0] * _position[2];
    _position[1] = coords[1] * _position[3];
}

}  // namespace checkers