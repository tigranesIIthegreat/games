#include "cell.hpp"

namespace checkers {

core::TextureRef Cell::_green_texture = std::make_shared<core::Texture>("green100");

Cell::Cell(core::Rect position, FigureRef figure)
    : core::Renderable(position, nullptr) {
    _components.push_back(figure);
}

FigureRef Cell::figure() {
    return std::static_pointer_cast<Figure>(_components[0]);
}

} // namespace checkers