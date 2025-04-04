#include <checkers/play_state.hpp>

#include <utils/log.hpp>

namespace checkers {

using namespace core;

PlayState::PlayState()
    : _current_player{Color::WHITE}, _current_selection{SelectionMode::SOURCE} {
    decltype(auto) window = Window::instance();
    auto board_size =
        static_cast<int>(std::min(window.width(), window.height()));
    auto board_texture = TextureFactory::instance().create("checkerboard");
    auto board = std::make_shared<Board>(Rect{0, 0, board_size, board_size},
                                         board_texture);
    _components.push_back(board);
    auto cell_size = board_size / board->size();

    Rect position{0, 0, cell_size, cell_size};
    for (int i{}; i < _figure_count / 2; ++i) {
        _figures[Color::WHITE].insert(std::make_shared<Man>(
            core::Coords{0, 0}, cell_size, Color::WHITE, board));
        _figures[Color::BLACK].insert(std::make_shared<Man>(
            core::Coords{0, 0}, cell_size, Color::BLACK, board));
    }
    _fill_board_with_figures();
    _current_player = Color::WHITE;
}

void PlayState::_fill_board_with_figures() {
    decltype(auto) board = std::static_pointer_cast<Board>(_components[0]);
    auto _white_iter = _figures[Color::WHITE].begin();
    auto _black_iter = _figures[Color::BLACK].begin();

    for (int i{}; i < _figure_count / 2; ++i, ++_white_iter, ++_black_iter) {
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
    auto& input_manager = core::input::InputManager::instance();
    bool mouse_clicked =
        input_manager.is_clicked(core::input::MouseButton::LEFT);
    if (mouse_clicked == false) {
        return;
    }
    CellRef cell_on_focus{};
    for (int i{}; i < board->size(); ++i) {
        for (int j{}; j < board->size(); ++j) {
            auto current_cell = board->at(i, j);
            if (current_cell->mouse_hovers_over()) {
                cell_on_focus = current_cell;
            }
        }
    }
    if (cell_on_focus == nullptr) {
        return;
    }
    _current_selection == SelectionMode::SOURCE
        ? handle_source_selection(cell_on_focus)
        : handle_destination_selection(cell_on_focus);
}

void PlayState::handle_source_selection(CellRef cell_on_focus) {
    if (cell_on_focus->figure() == nullptr) {
        return;
    }
    if (_current_player != cell_on_focus->figure()->color()) {
        return;
    }
    _valid_destinations = cell_on_focus->figure()->valid_destinations();
    if (_valid_destinations.empty()) {
        return;
    }
    cell_on_focus->select();
    _selected_source = cell_on_focus;
    std::for_each(_valid_destinations.begin(), _valid_destinations.end(),
                  [](auto& cell) { cell->select(); });
    switch_selection_modes();
}

void PlayState::switch_players() {
    int cur = static_cast<int>(_current_player);
    Logger::info(std::format("switching players : {} -> {}", cur, 1 - cur));
    _current_player = static_cast<Color>(1 - cur);
}

void PlayState::switch_selection_modes() {
    int cur = static_cast<int>(_current_selection);
    Logger::info(std::format("switching selection modes : {} -> {}", cur, 1 - cur));
    _current_selection = static_cast<SelectionMode>(1 - static_cast<int>(_current_selection));
}

void PlayState::remove_figures_between(CellRef src, CellRef dst) {
    auto src_x = src->coords()[1];
    auto src_y = src->coords()[0];

    auto dst_x = dst->coords()[1];
    auto dst_y = dst->coords()[0];

    if (std::abs(src_x - dst_x) != std::abs(src_y - dst_y)) {
        throw std::runtime_error("bad capture");
    }

    if (std::abs(src_x - dst_x) == 1) {
        return;
    }

    auto x_step = dst_x > src_x ? 1 : -1;
    auto y_step = dst_y > src_y ? 1 : -1;

    src_x += x_step;
    src_y += y_step;

    // dst_x -= x_step;
    // dst_y -= y_step;
    auto board = std::static_pointer_cast<Board>(_components[0]);
    for (int x = src_x, y = src_y; x != dst_x && y != dst_y;
         x += x_step, y += y_step) {
        if (board->at(x, y)->figure()) {
            Logger::info(std::format("removing: {} {}", x, y));
            board->at(x, y)->set_figure(nullptr);
        }
    }
}

void PlayState::handle_destination_selection(CellRef cell_on_focus) {
    auto board = std::static_pointer_cast<Board>(_components[0]);
    // the case we want to revert source selection
    if (cell_on_focus == _selected_source) {
        cell_on_focus->unselect();
        std::for_each(_valid_destinations.begin(), _valid_destinations.end(),
                      [](auto& cell) { cell->unselect(); });
        switch_selection_modes();
        return;
    }
    if (cell_on_focus->figure()) {
        return;
    }

    if (std::find(_valid_destinations.begin(), _valid_destinations.end(),
                  cell_on_focus) == _valid_destinations.end()) {
        return;
    }

    board->move(_selected_source, cell_on_focus);
    remove_figures_between(_selected_source, cell_on_focus);
    if (_current_player == Color::WHITE &&
        cell_on_focus->coords()[1] == board->size() - 1) {
        cell_on_focus->set_figure(std::make_shared<King>(
            cell_on_focus->coords(), board->cell_size(), Color::WHITE, board));
    }
    if (_current_player == Color::BLACK && cell_on_focus->coords()[1] == 0) {
        cell_on_focus->set_figure(std::make_shared<King>(
            cell_on_focus->coords(), board->cell_size(), Color::BLACK, board));
    }
    _selected_source->unselect();
    std::for_each(_valid_destinations.begin(), _valid_destinations.end(),
                  [](auto& cell) { cell->unselect(); });
    _selected_source = nullptr;
    _valid_destinations.clear();
    switch_players();
    switch_selection_modes();
}

}  // namespace checkers