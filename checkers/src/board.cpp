#include "board.hpp"
#include <utils/log.hpp>

#include <iostream>  // TODO: remove

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
    return y < _size && x < _size && ((x + y) % 2);
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
    if (_current_selection == SelectionMode::SOURCE) {
        if (cell_on_focus->figure() == nullptr) {
            return;
        }
        if (_current_player != cell_on_focus->figure()->color()) {
            return;
        }
        // TODO: check move availability
        cell_on_focus->select();
        _selected_source = cell_on_focus;
        switch_selection_modes();
    } else {
        // the case we want to revert source selection
        if (cell_on_focus == _selected_source) {
            cell_on_focus->unselect();
            switch_selection_modes();
            return;
        }
        if (cell_on_focus->figure()) {
            return;
        }

        move(_selected_source, cell_on_focus);
        _selected_source->unselect();
        _selected_source = nullptr;
        switch_players();
        switch_selection_modes();
    }
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
    // TODO: change arg types to Cell
    auto moving_figure = src->figure();
    dst->set_figure(moving_figure);
    src->set_figure(nullptr);
    moving_figure->set_coords(dst->coords());
}

}  // namespace checkers