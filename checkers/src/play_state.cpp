#include "play_state.hpp"

namespace checkers {

PlayState::PlayState(WindowRef window) 
    : core::GameState{window}
    , _player1{}
    , _player2{} {
    _board_size = std::min(_window->width(), _window->height());
    auto board_texture = std::make_shared<core::Texture>(
        "/Users/tigran.sukiasyan/games/assets/checkerboard.jpg", 1920, 1920,
        _window);
    _board = std::make_shared<Board>(core::Vec2{0, 0}, _board_size, _board_size,
                                     board_texture, _window);
    _cell_size = _board_size / _board->side_cell_count();
    auto white_man_texture = std::make_shared<core::Texture>(
        "/Users/tigran.sukiasyan/games/assets/man_white.webp", 310, 315,
        _window);
    auto black_man_texture = std::make_shared<core::Texture>(
        "/Users/tigran.sukiasyan/games/assets/man_black.webp", 310, 315,
        _window);
    for (size_t i{}; i < _figure_count / 2; ++i) {
        _white_figures.emplace_back(std::make_shared<Figure>(core::Vec2{0, 0}, _cell_size, _cell_size,
                                    white_man_texture, _window,
                                    core::Vec2{0, 0}, core::Vec2{0, 0},
                                    FigureColor::WHITE, false));
        _black_figures.emplace_back(std::make_shared<Figure>(core::Vec2{0, 0}, _cell_size, _cell_size,
                                    black_man_texture, _window, core::Vec2{0, 0},
                                    core::Vec2{0, 0}, FigureColor::BLACK, false));
    }
}

void PlayState::fill_board_with_figures() {
    for (size_t i{}; i < _figure_count / 2; ++i) {
        auto side_cell_count = _board->side_cell_count();

        // set a white figure on the top
        auto white_figure_x = (i + 1) % side_cell_count;
        auto white_figure_y = (i + 1) / side_cell_count;
        auto white_figure = _white_figures[i];
        _board->at(white_figure_y, white_figure_x) = white_figure;

        // set a black figure on the bottom
        auto black_figure_x = side_cell_count - white_figure_x;
        auto black_figure_y = side_cell_count - white_figure_y;
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