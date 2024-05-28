#pragma once

#include "figure.hpp"
#include <core/input.hpp>
#include <core/renderable.hpp>
#include <core/texture.hpp>

namespace checkers {

class Cell : public core::Renderable, public core::input::Inputable {
public:
    Cell(core::Rect position, FigureRef figure = nullptr);
    FigureRef figure();
    void set_figure(FigureRef figure);
    virtual void handle_inputs() override;

private:
    static core::TextureRef _green_texture;
};

using CellRef = std::shared_ptr<Cell>;

} // namespace checkers