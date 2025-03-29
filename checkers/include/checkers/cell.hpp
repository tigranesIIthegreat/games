#pragma once

#include "figure.hpp"

namespace checkers {

class Cell : public core::GameObject {
public:
    Cell(core::Coords coords, int size, FigureRef figure = nullptr);
    FigureRef figure();
    void set_figure(FigureRef figure);
    virtual void handle_inputs() override;

public:
    void select();
    void unselect();
    bool is_selected() const;
    core::Coords coords() const;
    void set_coords(core::Coords cords);

private:
    bool _is_selected{};

private:
    static core::TextureRef _green25_texture;
    static core::TextureRef _green50_texture;
};

using CellRef = std::shared_ptr<Cell>;

}  // namespace checkers