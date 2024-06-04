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

Figure::Figure(core::Rect position, Color color)
    : InteractiveRenderable{position, nullptr}
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

void Figure::set_selected(bool selected) {
    _is_selected = selected;
}

void Figure::handle_inputs() {
    if (mouse_hovers_over()) {
        // TODO: mouse hovers
    } else {
        // TODO: mouse does not hover
    }
}

}  // namespace checkers