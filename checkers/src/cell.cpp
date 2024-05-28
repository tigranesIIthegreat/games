#include "cell.hpp"

namespace checkers {

core::TextureRef Cell::_green_texture = std::make_shared<core::Texture>("green100");

Cell::Cell(core::Rect position, std::optional<FigureRef> figure)
    : core::Renderable(position, nullptr)
    , figure{figure} {}

} // namespace checkers