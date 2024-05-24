#include "board.hpp"

namespace checkers {

Board::Board(Rect position, TextureRef texture)
    : Renderable{position, texture} {}

bool Board::is_valid_position(size_t y, size_t x) const {
    // dark squares of the board are considered to be valid
    return y < _size && x < _size && ((x + y) % 2);
}

Cell& Board::at(size_t x, size_t y) {
    return _cells.at(x).at(y);
}

size_t Board::size() {
    return _size;
}

}  // namespace checkers