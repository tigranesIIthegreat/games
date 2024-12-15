#include "cell.hpp"

namespace checkers {

core::TextureRef Cell::_green25_texture =
    std::make_shared<core::Texture>("green25");

core::TextureRef Cell::_green50_texture =
    std::make_shared<core::Texture>("green50");

Cell::Cell(core::Rect position, FigureRef figure)
    : core::GameObject(position, nullptr) {
    _components.push_back(figure);
}

FigureRef Cell::figure() {
    return std::static_pointer_cast<Figure>(_components[0]);
}

void Cell::set_figure(FigureRef figure) {
    _components[0] = figure;
    if (figure == nullptr) {
        return;
    }
    figure->set_coords(core::Point{_position[0], _position[1]});
}

void Cell::handle_inputs() {
    // TODO: consider some input handling
}

bool Cell::can_be_selected() const {
    return _can_be_selected;
}

void Cell::set_can_be_selected(bool can_be_selected) {
    _can_be_selected = can_be_selected;
}

bool Cell::is_selected() const {
    return _is_selected;
}

void Cell::set_selected(bool selected) {
    _is_selected = selected;
}

void Cell::select() {
    _texture = _green50_texture;
    _is_selected = true;
}

void Cell::unselect() {
    _texture = nullptr;
    _is_selected = false;
}

}  // namespace checkers