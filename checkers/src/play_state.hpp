#pragma once

#include <core/game_state.hpp>
#include <core/window.hpp>
#include <set>
#include "board.hpp"
#include "color.hpp"
#include "king.hpp"
#include "man.hpp"

namespace checkers {

class PlayState : public core::GameState {
public:
    PlayState();

public:
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual std::string name() override;

private:
    void _fill_board_with_figures();
    void _switch_players();

private:
    void handle_source_selection(CellRef cell_on_focus);
    void handle_destination_selection(CellRef cell_on_focus);
    void remove_figures_between(CellRef src, CellRef dst);
    void switch_players();
    void switch_selection_modes();

protected:
    virtual void handle_inputs() override;

private:
    static constexpr int _figure_count = 24;

private:
    std::map<Color, std::set<FigureRef>> _figures;
    Color _current_player;
    SelectionMode _current_selection;
    CellRef _selected_source{};
    std::vector<CellRef> _valid_destinations{};
};

}  // namespace checkers