#pragma once

#include "figure.hpp"
#include <core/renderable.hpp>
#include <core/texture.hpp>

namespace checkers {

class Cell : public core::Renderable {
public:
    Cell(core::Rect position, FigureRef figure = nullptr);
    FigureRef figure();

private:
    static core::TextureRef _green_texture;
};

using CellRef = std::shared_ptr<Cell>;

} // namespace checkers