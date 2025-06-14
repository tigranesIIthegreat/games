#include <checkers/board.hpp>

#include <checkers/king.hpp>
#include <utils/log.hpp>

namespace checkers {

Board::Board(Rect position, TextureRef texture)
    : GameObject{position, texture} {
    decltype(auto) window = Window::instance();
    _cell_size = position[2] / _size;
    _components.reserve(_size * _size);
    for (int i{}; i < _size; ++i) {
        for (int j{}; j < _size; ++j) {
            auto cell_x = position[0] + i * _cell_size;
            auto cell_y = position[1] + j * _cell_size;
            auto position = Rect{cell_x, cell_y, _cell_size, _cell_size};
            auto coords = Coords{i, j};
            _components.push_back(std::make_shared<Cell>(position, coords));
        }
    }
}

bool Board::is_valid_position(int x, int y) const {
    // dark squares of the board are considered to be valid
    return 0 <= y && y < _size && 0 <= x && x < _size && ((x + y) % 2);
}

CellRef Board::at(int x, int y) {
    // TODO: understand why (x * _size + y) did not for diagonally !?!?!?
    return std::static_pointer_cast<Cell>(_components.at(y * _size + x));
}

int Board::size() {
    return _size;
}

int Board::cell_size() const {
    return _cell_size;
}

void Board::handle_inputs() {
    // empty
}

void Board::move(CellRef src, CellRef dst) {
    // TODO: add proper error handling
    auto moving_figure = src->figure();
    dst->set_figure(moving_figure);
    src->set_figure(nullptr);
    moving_figure->set_coords(dst->coords());
}

}  // namespace checkers