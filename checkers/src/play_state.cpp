#include "play_state.hpp"

namespace checkers {

using namespace core;

PlayState::PlayState() {
    decltype(auto) window = Window::get_instance();
    auto board_size = static_cast<float>(std::min(window.width(), window.height()));
    auto board_texture = std::make_shared<Texture>("checkerboard");
    auto board = std::make_shared<Board>(Rect{0, 0, board_size, board_size},
                                         board_texture);
    _components.push_back(board);
    auto cell_size = board_size / board->size();
    auto white_man_texture = std::make_shared<Texture>("man_white");
    auto black_man_texture = std::make_shared<Texture>("man_black");
    Rect position{0, 0, cell_size, cell_size};
    for (size_t i{}; i < _figure_count / 2; ++i) {
        _figures[Color::WHITE].insert(std::make_shared<Figure>(position, Color::WHITE));
        _figures[Color::BLACK].insert(std::make_shared<Figure>(position, Color::BLACK));
    }
    _fill_board_with_figures();
    _current_player = Color::WHITE;
}

void PlayState::_fill_board_with_figures() {
    decltype(auto) board = std::static_pointer_cast<Board>(_components[0]);
    auto _white_iter = _figures[Color::WHITE].begin();
    auto _black_iter = _figures[Color::BLACK].begin();

    for (size_t i{}; i < _figure_count / 2; ++i, ++_white_iter, ++_black_iter) {
        auto size = board->size();

        // set a white figure on the top
        auto cell_number = 2 * i;
        auto white_x = cell_number % size;
        auto white_y = cell_number / size;
        if (!board->is_valid_position(white_y, white_x)) {
            ++white_x;
        }
        board->at(white_y, white_x)->set_figure(*_white_iter);

        // set a black figure on the bottom
        auto black_x = size - 1 - white_x;
        auto black_y = size - 1 - white_y;
        if (!board->is_valid_position(black_y, black_x)) {
            ++black_x;
        }
        board->at(black_y, black_x)->set_figure(*_black_iter);
    }
}

void PlayState::_switch_players() {
    if (_current_player == Color::WHITE) {
        _current_player = Color::BLACK;
    } else {
        _current_player = Color::WHITE;
    }
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