#include "cell.hpp"

namespace checkers {

core::TextureRef Cell::_green_texture = std::make_shared<core::Texture>("green50");

Cell::Cell(core::Rect position, FigureRef figure)
    : core::Renderable(position, nullptr) {
    _components.push_back(figure);
}

FigureRef Cell::figure() {
    return std::static_pointer_cast<Figure>(_components[0]);
}

void Cell::set_figure(FigureRef figure) {
    _components[0] = figure;
}

void Cell::handle_inputs() {
    auto mouse_position = core::input::InputManager::get_instance().mouse_position();
    if (_position[0] <= mouse_position[0] and
        mouse_position[0] <= _position[0] + _position[2] and
        _position[1] <= mouse_position[1] and
        mouse_position[1] <= _position[1] + _position[3]) {

        _texture = _green_texture;
    } else {
        _texture = nullptr;
    }
}

} // namespace checkers