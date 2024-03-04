#include "board.hpp"

namespace checkers {

void Board::update() {
    Renderable::update();
    for (auto& row : _cells) {
        for (auto& cell : row) {
            if (cell.has_value()) {
                cell.value()->update();
            }
        }
    }
}

void Board::render() {
    Renderable::render();
    for (auto& row : _cells) {
        for (auto& cell : row) {
            if (cell.has_value()) {
                cell.value()->render();
            }
        }
    }
}

bool Board::is_valid_position(size_t y, size_t x) const {
    // dark squares of the board are considered to be valid
    return y < _size && x < _size && ((x + y) % 2);
}

std::optional<FigureRef> Board::at(size_t x, size_t y) {
    return _cells.at(x).at(y);
}

constexpr size_t Board::size() const {
    return _size;
}

} // namespace checkers