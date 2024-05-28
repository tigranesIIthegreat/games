#include "cell.hpp"

namespace checkers {

core::TextureRef Cell::_green_texture = std::make_shared<core::Texture>("green50");

Cell::Cell(core::Rect position, FigureRef figure)
    : core::InteractiveRenderable(position, nullptr) {
    _components.push_back(figure);
}

FigureRef Cell::figure() {
    return std::static_pointer_cast<Figure>(_components[0]);
}

void Cell::set_figure(FigureRef figure) {
    _components[0] = figure;
}

void Cell::handle_inputs() {
    if (mouse_hovers()) {
        _texture = _green_texture;
    } else {
        _texture = nullptr;
    }
}

} // namespace checkers