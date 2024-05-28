#include "board.hpp"

namespace checkers {

Board::Board(Rect position, TextureRef texture)
    : Renderable{position, texture} {
    decltype(auto) window = Window::get_instance();
    float cell_size = std::min(window.width(), window.height()) / _size;
    for (size_t i{}; i < _size; ++i) {
        for (size_t j{}; j < _size; ++j) {
            auto position = Rect{(i - 1) * cell_size, (j - 1) * cell_size,
                                 cell_size, cell_size};
            _cells[i][j] = Cell(position);
        }
    }
}

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