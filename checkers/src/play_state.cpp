#include "play_state.hpp"

namespace checkers {

using namespace core;

PlayState::PlayState() {
    decltype(auto) window = Window::get_instance();
    _board_size = std::min(window.width(), window.height());
    auto board_texture = std::make_shared<Texture>("checkerboard");
    auto board = std::make_shared<Board>(Rect{0, 0, _board_size, _board_size},
                                         board_texture);
    _components.push_back(board);
    _cell_size = _board_size / board->size();
    auto white_man_texture = std::make_shared<Texture>("man_white");
    auto black_man_texture = std::make_shared<Texture>("man_black");
    Rect figure_position{0, 0, _cell_size, _cell_size};
    for (size_t i{}; i < _figure_count / 2; ++i) {
        _white_figures.emplace_back(std::make_shared<Figure>(
            figure_position, white_man_texture, Color::WHITE, false));
        _black_figures.emplace_back(std::make_shared<Figure>(
            figure_position, black_man_texture, Color::BLACK, false));
    }
    _fill_board_with_figures();
    _current_player = Color::WHITE;
}

void PlayState::_fill_board_with_figures() {
    decltype(auto) board = std::static_pointer_cast<Board>(_components[0]);
    for (size_t i{}; i < _figure_count / 2; ++i) {
        auto size = board->size();

        // set a white figure on the top
        auto cell_number = 2 * i;
        auto white_x = cell_number % size;
        auto white_y = cell_number / size;
        if (!board->is_valid_position(white_y, white_x)) {
            ++white_x;
        }
        auto white = _white_figures[i];
        white->set_coords(Point{white_x * _cell_size, white_y * _cell_size});
        board->at(white_y, white_x)->set_figure(white);

        // set a black figure on the bottom
        auto black_x = size - 1 - white_x;
        auto black_y = size - 1 - white_y;
        if (!board->is_valid_position(black_y, black_x)) {
            ++black_x;
        }
        auto black = _black_figures[i];
        black->set_coords(Point{black_x * _cell_size, black_y * _cell_size});
        board->at(black_y, black_x)->set_figure(black);
    }
}

void PlayState::_switch_players() {
    _current_player =
        _current_player == Color::WHITE ? Color::BLACK : Color::WHITE;
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
    auto board = std::static_pointer_cast<Board>(_components[0]);
    board->handle_inputs();
}

}  // namespace checkers