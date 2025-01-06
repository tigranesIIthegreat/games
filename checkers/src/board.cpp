#include "board.hpp"
#include <utils/log.hpp>
#include "king.hpp"

namespace checkers {

Board::Board(Rect position, TextureRef texture)
    : GameObject{position, texture},
      _current_player{Color::WHITE},
      _current_selection{SelectionMode::SOURCE} {
    decltype(auto) window = Window::instance();
    _cell_size = std::min(window.width(), window.height()) / _size;
    _components.reserve(_size * _size);
    for (int i{}; i < _size; ++i) {
        for (int j{}; j < _size; ++j) {
            auto position =
                Rect{i * _cell_size, j * _cell_size, _cell_size, _cell_size};
            auto coords = Coords{i, j};
            _components.push_back(std::make_shared<Cell>(coords, _cell_size));
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

void Board::handle_inputs() {
    auto& input_manager = core::input::InputManager::instance();
    bool mouse_clicked =
        input_manager.is_clicked(core::input::MouseButton::LEFT);
    if (mouse_clicked == false) {
        return;
    }
    CellRef cell_on_focus{};
    for (int i{}; i < _size; ++i) {
        for (int j{}; j < _size; ++j) {
            auto current_cell = this->at(i, j);
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

void Board::switch_players() {
    int current = static_cast<int>(_current_player);
    Logger::instance().info("switching players : %d -> %d", current,
                            1 - current);
    _current_player = static_cast<Color>(1 - current);
}

void Board::switch_selection_modes() {
    int current = static_cast<int>(_current_selection);
    Logger::instance().info("switching selection modes : %d -> %d", current,
                            1 - current);
    _current_selection =
        static_cast<SelectionMode>(1 - static_cast<int>(_current_selection));
}

void Board::move(CellRef src, CellRef dst) {
    // TODO: add proper error handling
    auto moving_figure = src->figure();
    dst->set_figure(moving_figure);
    src->set_figure(nullptr);
    moving_figure->set_coords(dst->coords());
}

void Board::handle_source_selection(CellRef cell_on_focus) {
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

void Board::handle_destination_selection(CellRef cell_on_focus) {
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

    move(_selected_source, cell_on_focus);
    remove_figures_between(_selected_source, cell_on_focus);
    if (_current_player == Color::WHITE &&
        cell_on_focus->coords()[1] == _size - 1) {
        cell_on_focus->set_figure(
            std::make_shared<King>(cell_on_focus->coords(), _cell_size,
                                   Color::WHITE, shared_from_this()));
    }
    if (_current_player == Color::BLACK && cell_on_focus->coords()[1] == 0) {
        cell_on_focus->set_figure(
            std::make_shared<King>(cell_on_focus->coords(), _cell_size,
                                   Color::BLACK, shared_from_this()));
    }
    _selected_source->unselect();
    std::for_each(_valid_destinations.begin(), _valid_destinations.end(),
                  [](auto& cell) { cell->unselect(); });
    _selected_source = nullptr;
    _valid_destinations.clear();
    switch_players();
    switch_selection_modes();
}

void Board::remove_figures_between(CellRef src, CellRef dst) {
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

    for (int x = src_x, y = src_y; x != dst_x && y != dst_y;
         x += x_step, y += y_step) {
        if (at(x, y)->figure()) {
            Logger::instance().info("removing: %d %d", x, y);
            at(x, y)->set_figure(nullptr);
        }
    }
}

}  // namespace checkers