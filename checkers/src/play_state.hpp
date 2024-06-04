#pragma once

#include "board.hpp"
#include "color.hpp"
#include "figure.hpp"
#include <core/game_state.hpp>
#include <core/window.hpp>
#include <set>

namespace checkers {

enum class SelectionMode { SOURCE = 0, DESTINATION = 1 };

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

// private:
//     std::set<CellRef> _valid_sources_of(Color player);
//     std::set<CellRef> _valid_destinations_of(CellRef source);
//     void _move_figure(CellRef source, CellRef destination);

protected:
    virtual void handle_inputs() override;

private:
    static constexpr size_t _figure_count = 24;

private:
    float _board_size;
    float _cell_size;
    std::vector<FigureRef> _whites;
    std::vector<FigureRef> _blacks;
    Color _current_player;
    // SelectionMode _current_mode;
};

}  // namespace checkers