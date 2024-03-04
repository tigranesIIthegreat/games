#pragma once

#include "board.hpp"
#include "figure.hpp"
#include "player.hpp"

#include <core/game_state.hpp>

#include <array>

namespace checkers {

class PlayState : public core::GameState {
public:
    static constexpr size_t figure_count = 24;

private:
    void fill_board_with_figures();

private:
    BoardRef _board;
    std::array<FigureRef, figure_count / 2> _white_figures;
    std::array<FigureRef, figure_count / 2> _black_figures;
    PlayerRef _player1;
    PlayerRef _player2;
};

} // namespace checkers