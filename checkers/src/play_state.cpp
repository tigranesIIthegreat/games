#include "play_state.hpp"

namespace checkers {

PlayState::PlayState(WindowRef window) 
    : _window{window}
    , _player1{}
    , _player2{} {
}

void PlayState::fill_board_with_figures() {
    for (size_t i{}; i < figure_count / 2; ++i) {
        auto board_size = _board->size();

        // set a white figure on the top
        auto white_figure_x = (i + 1) % board_size;
        auto white_figure_y = (i + 1) / board_size;
        auto white_figure = _white_figures[i];
        _board->at(white_figure_y, white_figure_x) = white_figure;

        // set a black figure on the bottom
        auto black_figure_x = board_size - white_figure_x;
        auto black_figure_y = board_size - white_figure_y;
        auto black_figure = _black_figures[i];
        _board->at(black_figure_y, black_figure_x) = black_figure;
    }
}

void PlayState::render() {
    _board->render();
}

void PlayState::update() {
    // TODO:
}

void PlayState::on_enter() {
    // TODO:
}

void PlayState::on_exit() {
    // TODO:
}

std::string PlayState::name() {
    return "play";
}

} // namespace checkers