#include "play_state.hpp"

namespace checkers {

using namespace core;

PlayState::PlayState() {
    decltype(auto) window = Window::get_instance();
    _board_size = std::min(window.width(), window.height());
    auto board_texture = std::make_shared<Texture>("checkerboard");
    _board = std::make_shared<Board>(Rect{0, 0, _board_size, _board_size},
                                     board_texture);
    _cell_size = _board_size / _board->size();
    auto white_man_texture = std::make_shared<Texture>("man_white");
    auto black_man_texture = std::make_shared<Texture>("man_black");
    Rect figure_position{0, 0, _cell_size, _cell_size};
    for (size_t i{}; i < _figure_count / 2; ++i) {
        _white_figures.emplace_back(std::make_shared<Figure>(
            figure_position, white_man_texture,
            FigureColor::WHITE, false));
        _black_figures.emplace_back(std::make_shared<Figure>(
            figure_position, black_man_texture,
            FigureColor::BLACK, false));
    }
    _fill_board_with_figures();

    _players[0] = std::make_shared<Player>("player1", _white_figures);
    _players[1] = std::make_shared<Player>("player2", _black_figures);
    _current_player_index = 0;
}

void PlayState::_fill_board_with_figures() {
    for (size_t i{}; i < _figure_count / 2; ++i) {
        auto size = _board->size();

        // set a white figure on the top
        auto cell_number = 2 * i;
        auto white_x = cell_number % size;
        auto white_y = cell_number / size;
        if (!_board->is_valid_position(white_y, white_x)) {
            ++white_x;
        }
        auto white = _white_figures[i];
        white->set_coords(Point{white_x * _cell_size, white_y * _cell_size});
        _board->at(white_y, white_x)->figure() = white;

        // set a black figure on the bottom
        auto black_x = size - 1 - white_x;
        auto black_y = size - 1 - white_y;
        if (!_board->is_valid_position(black_y, black_x)) {
            ++black_x;
        }
        auto black = _black_figures[i];
        black->set_coords(Point{black_x * _cell_size, black_y * _cell_size});
        _board->at(black_y, black_x)->figure() = black;
    }
}

void PlayState::_switch_players() {
    _current_player_index = 1 - _current_player_index;
}

void PlayState::render() {
    _board->render();
    decltype(auto) render = std::mem_fn(&Figure::render);
    std::for_each(_white_figures.begin(), _white_figures.end(), render);
    std::for_each(_black_figures.begin(), _black_figures.end(), render);
}

void PlayState::run() {
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

void PlayState::handle_inputs() {
    for (auto& figure : _white_figures) {
        figure->handle_inputs();
    }
    for (auto& figure : _black_figures) {
        figure->handle_inputs();
    }
}

}  // namespace checkers