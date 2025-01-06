#pragma once

#include <array>
#include <core/game_object.hpp>
#include <memory>
#include "cell.hpp"
#include "color.hpp"
#include "figure.hpp"

namespace checkers {

using namespace core;

enum class SelectionMode { SOURCE = 0, DESTINATION = 1 };

class Board : public GameObject, public std::enable_shared_from_this<Board> {
public:
    Board(Rect position, TextureRef texture);
    virtual void handle_inputs() override;

public:
    void move(CellRef src, CellRef dst);
    bool is_valid_position(int x, int y) const;
    CellRef at(int x, int y);
    static int size();

private:
    void handle_source_selection(CellRef cell_on_focus);
    void handle_destination_selection(CellRef cell_on_focus);
    void remove_figures_between(CellRef src, CellRef dst);
    void switch_players();
    void switch_selection_modes();

private:
    int _cell_size{};
    Color _current_player;
    SelectionMode _current_selection;
    CellRef _selected_source{};
    std::vector<CellRef> _vd{};

private:
    static constexpr int _size = 8;
};

using BoardRef = std::shared_ptr<Board>;

}  // namespace checkers