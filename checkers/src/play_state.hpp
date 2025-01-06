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

protected:
    virtual void handle_inputs() override;

private:
    static constexpr int _figure_count = 24;

private:
    std::map<Color, std::set<FigureRef>> _figures;
    Color _current_player;
};

}  // namespace checkers