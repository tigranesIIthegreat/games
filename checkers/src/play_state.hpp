#pragma once

#include "board.hpp"
#include "figure.hpp"
#include "player.hpp"

#include <core/game_state.hpp>
#include <core/window.hpp>

#include <array>

namespace checkers {

class PlayState : public core::GameState {
public:
    PlayState(WindowRef window);

public:
    virtual void on_enter() override;
    virtual void on_exit() override;
    virtual void update() override;
    virtual void render() override;
    virtual std::string name() override;

private:
    void fill_board_with_figures();

private:
    static constexpr size_t figure_count = 24;

private:
    WindowRef _window;
    PlayerRef _player1;
    PlayerRef _player2;
    std::array<FigureRef, figure_count / 2> _white_figures;
    std::array<FigureRef, figure_count / 2> _black_figures;
    BoardRef _board;
};

} // namespace checkers