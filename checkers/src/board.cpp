#include "board.hpp"

namespace checkers {

bool Board::is_valid_position(size_t y, size_t x) const {
    // dark squares of the board are considered to be valid
    return y < size && x < size && ((x + y) % 2);
}

void Board::fill_with_figures(const std::array<FigureRef, figure_count>& figures) {
    for (size_t i{}; i < figure_count / 2; ++i) {
        // set a white figure on the top
        auto white_figure_x = (i + 1) % size;
        auto white_figure_y = (i + 1) / size;
        auto white_figure = figures[i];
        _figures[white_figure_y][white_figure_x] = white_figure;

        // set a black figure on the bottom
        auto black_figure_x = size - white_figure_x;
        auto black_figure_y = size - white_figure_y;
        auto black_figure = figures[figures.size() - 1 - i];
        _figures[black_figure_y][black_figure_x] = black_figure;
    }
}

} // namespace checkers