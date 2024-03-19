#include "play_state.hpp"

namespace checkers {

using namespace core;

PlayState::PlayState(WindowRef window) 
    : GameState{window} {
    _board_size = std::min(_window->width(), _window->height());
    auto board_texture = std::make_shared<Texture>("checkerboard", _window);
    _board = std::make_shared<Board>(Vec2{0, 0}, _board_size, _board_size, board_texture, _window);
    _cell_size = _board_size / _board->side_cell_count();
    auto white_man_texture = std::make_shared<Texture>("man_white", _window);
    auto black_man_texture = std::make_shared<Texture>("man_black", _window);
    for (size_t i{}; i < _figure_count / 2; ++i) {
        _white_figures.emplace_back(std::make_shared<Figure>(Vec2{0, 0}, _cell_size, _cell_size,
                                    white_man_texture, _window, FigureColor::WHITE, false));
        _black_figures.emplace_back(std::make_shared<Figure>(Vec2{0, 0}, _cell_size, _cell_size,
                                    black_man_texture, _window, FigureColor::BLACK, false));
    }
    _fill_board_with_figures();

    _players[0] = std::make_shared<Player>("player1", _white_figures);
    _players[1] = std::make_shared<Player>("player2", _black_figures);
    _current_player_index = 0;
}

void PlayState::_fill_board_with_figures() {
    for (size_t i{}; i < _figure_count / 2; ++i) {
        auto side_cell_count = _board->side_cell_count();

        // set a white figure on the top
        auto cell_number = 2 * i;
        auto white_x = cell_number % side_cell_count;
        auto white_y = cell_number / side_cell_count;
        if (!_board->is_valid_position(white_y, white_x)) {
            ++white_x;
        }
        auto white = _white_figures[i];
        white->set_coords(Vec2{white_x * _cell_size, white_y * _cell_size});
        _board->at(white_y, white_x) = white;

        // set a black figure on the bottom
        auto black_x = side_cell_count - 1 - white_x;
        auto black_y = side_cell_count - 1 - white_y;
        if (!_board->is_valid_position(black_y, black_x)) {
            ++black_x;
        }
        auto black = _black_figures[i];
        black->set_coords(Vec2{black_x * _cell_size, black_y * _cell_size});
        _board->at(black_y, black_x) = black;
    }
}

void PlayState::_switch_players() {
    _current_player_index = 1 - _current_player_index;
}

void PlayState::render() {
    _board->render();
}

void PlayState::update() {
    // TODO:
}

void PlayState::one_iteration() {
    _players[_current_player_index]->play();
    _switch_players();
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