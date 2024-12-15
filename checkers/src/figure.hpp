#pragma once

#include <core/game_object.hpp>
#include <memory>
#include "color.hpp"

namespace checkers {

class Board;
using BoardRef = std::shared_ptr<Board>;

class Cell;
using CellRef = std::shared_ptr<Cell>;

class Figure : public core::GameObject {
public:
    Figure(core::Coords coords, int size, Color color, BoardRef board);

    Color color() const;
    core::Coords coords() const;
    void set_coords(core::Coords cords);
    virtual std::vector<CellRef> valid_destinations() const = 0;

protected:
    const Color _color;
    BoardRef _board;
};

using FigureRef = std::shared_ptr<Figure>;

}  // namespace checkers