#include "figure.hpp"

#include <iostream>

namespace checkers {

Figure::Figure(core::Rect position, core::TextureRef texture,
               FigureColor color,
               bool is_king)
    : InteractiveRenderable{position, texture}
    , _color{color}
    , _is_king{is_king}
    , _is_selected{false} {}

FigureColor Figure::color() const {
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
    auto mouse_position = core::input::InputManager::get_instance().mouse_position();
    if (_position[0] <= mouse_position[0] and
        mouse_position[0] <= _position[0] + _position[2] and
        _position[1] <= mouse_position[1] and
        mouse_position[1] <= _position[1] + _position[3]) {

        // TODO: mouse hovers
    } else {
        // TODO: mouse does not hover
    }
}

}  // namespace checkers