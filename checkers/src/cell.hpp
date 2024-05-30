#pragma once

#include "figure.hpp"

namespace checkers {

class Cell : public core::InteractiveRenderable {
public:
    Cell(core::Rect position, FigureRef figure = nullptr);
    FigureRef figure();
    void set_figure(FigureRef figure);
    virtual void handle_inputs() override;

private:
    static core::TextureRef _green25_texture;
    static core::TextureRef _green50_texture;
};

using CellRef = std::shared_ptr<Cell>;

}  // namespace checkers