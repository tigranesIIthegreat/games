#include "board.hpp"

namespace checkers {

Board::Board(Rect position, TextureRef texture)
    : Renderable{position, texture} {}


bool Board::is_valid_position(size_t y, size_t x) const {
    // dark squares of the board are considered to be valid
    return y < _side_cell_count && x < _side_cell_count && ((x + y) % 2);
}

std::optional<FigureRef>& Board::at(size_t x, size_t y) {
    return _cells.at(x).at(y);
}

size_t Board::side_cell_count() const {
    return _side_cell_count;
}

}  // namespace checkers