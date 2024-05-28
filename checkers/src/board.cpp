#include "board.hpp"

namespace checkers {

Board::Board(Rect position, TextureRef texture)
    : Renderable{position, texture} {
    decltype(auto) window = Window::get_instance();
    float cell_size = std::min(window.width(), window.height()) / _size;
    _components.reserve(_size * _size);
    for (size_t i{}; i < _size; ++i) {
        for (size_t j{}; j < _size; ++j) {
            auto position = Rect{i * cell_size, j * cell_size,
                                 cell_size, cell_size};
            _components.push_back(std::make_shared<Cell>(position));
        }
    }
}

bool Board::is_valid_position(size_t y, size_t x) const {
    // dark squares of the board are considered to be valid
    return y < _size && x < _size && ((x + y) % 2);
}

CellRef Board::at(size_t x, size_t y) {
    return std::static_pointer_cast<Cell>(_components.at(x * _size + y));
}

size_t Board::size() {
    return _size;
}

}  // namespace checkers