#pragma once

#include "board.hpp"
#include "figure.hpp"
#include "player.hpp"

#include <core/game_state.hpp>
#include <core/window.hpp>

#include <vector>

namespace checkers {

class PlayState : public core::GameState {
public:
    PlayState(WindowRef window);

public:
    virtual void one_iteration() override;
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void update() override;
    virtual void render() override;
    virtual std::string name() override;

private:
    void _fill_board_with_figures();
    void _switch_players();

private:
    static constexpr size_t _figure_count = 24;

private:
    float _board_size;
    BoardRef _board;
    float _cell_size;
    std::vector<FigureRef> _white_figures;
    std::vector<FigureRef> _black_figures;
    std::array<PlayerRef, 2> _players;
    std::size_t _current_player_index;
};

} // namespace checkers